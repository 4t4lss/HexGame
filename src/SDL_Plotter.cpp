/**
 * @file SDL_Plotter.cpp
 * @brief SDL3 implementation of the SDL_Plotter graphics and sound wrapper.
 *
 * @author Dr. Booth
 * @version 4.0
 * @date 2026-08-29
 *
 * @details
 * This implementation is derived from the SDL2 version of SDL_Plotter and has
 * been migrated to SDL3 and SDL3_mixer.  Significant migration changes include:
 *
 * - SDL_CreateWindow() no longer accepts explicit x/y window-position values.
 * - SDL_CreateRenderer() now accepts a renderer name rather than a driver index.
 * - SDL_RenderCopy() has been replaced by SDL_RenderTexture().
 * - SDL event constants use the SDL_EVENT_* names.
 * - SDL3 text-input events must be explicitly enabled.
 * - SDL_GetMouseState() and mouse events expose floating-point coordinates.
 * - SDL3_mixer uses MIX_Mixer and MIX_Audio rather than Mix_Chunk/channels.
 *
 * The public SDL_Plotter interface remains intentionally close to the earlier
 * version so existing course programs can migrate with minimal modification.
 */

#include "SDL_Plotter.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

/** Packed ARGB8888 value used by clear() for an opaque white pixel. */
const Uint32 OPAQUE_WHITE = 0xFFFFFFFFu;

/**
 * @brief Builds a runtime-error message from the current SDL error string.
 * @param operation Description of the SDL operation that failed.
 * @return Combined human-readable error message.
 */
std::string makeSDLError(const std::string& operation) {
    const char* error = SDL_GetError();
    return operation + ": " + ((error != nullptr) ? error : "unknown SDL error");
}

}  // namespace

// -----------------------------------------------------------------------------
// Construction and destruction
// -----------------------------------------------------------------------------

SDL_Plotter::SDL_Plotter(int r, int c, bool WITH_SOUND)
    : texture(nullptr),
      renderer(nullptr),
      window(nullptr),
      pixels(),
      event(),
      row(r),
      col(c),
      quit(false),
      key_queue(),
      click_queue(),
      SOUND(false),
      mixer(nullptr),
      soundMap() {

    // A zero-sized or negative drawing area cannot produce a valid SDL texture.
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("SDL_Plotter dimensions must be positive");
    }

    // Allocate the CPU-side pixel buffer before acquiring SDL resources.  This
    // avoids leaking SDL objects if vector allocation throws an exception.
    pixels.assign(static_cast<std::size_t>(row) *
                      static_cast<std::size_t>(col),
                  OPAQUE_WHITE);

    // SDL3 requires the video subsystem to be initialized before a window and
    // renderer are created.
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(makeSDLError("SDL_Init(SDL_INIT_VIDEO) failed"));
    }

    // SDL3 removed the explicit window-position arguments used by SDL2.
    window = SDL_CreateWindow("SDL3 Pixel Drawing", col, row, 0);
    if (window == nullptr) {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        throw std::runtime_error(makeSDLError("SDL_CreateWindow failed"));
    }

    // Passing nullptr asks SDL3 to select an appropriate rendering driver.
    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        throw std::runtime_error(makeSDLError("SDL_CreateRenderer failed"));
    }

    // The public getColor() method historically exposes the packed ARGB8888
    // pixel representation, so that format is retained in the SDL3 version.
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STATIC,
                                col,
                                row);
    if (texture == nullptr) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        renderer = nullptr;
        window = nullptr;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        throw std::runtime_error(makeSDLError("SDL_CreateTexture failed"));
    }

    // SDL3 defaults alpha-capable textures to alpha blending.  The historical
    // SDL_Plotter pixel encoding does not set alpha for plotted RGB pixels, so
    // disabling texture blending preserves the visible behavior of the SDL2
    // implementation and preserves getColor()'s packed pixel values.
    if (!SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE)) {
        SDL_LogWarn(SDL_LOG_CATEGORY_RENDER,
                    "SDL_Plotter: unable to disable texture blending: %s",
                    SDL_GetError());
    }

    // SDL3 does not emit SDL_EVENT_TEXT_INPUT events unless text input has been
    // explicitly enabled for the window.
    if (!SDL_StartTextInput(window)) {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
                    "SDL_Plotter: unable to enable text input: %s",
                    SDL_GetError());
    }

    // Sound is optional.  Graphics remain usable if SDL3_mixer or the default
    // playback device cannot be initialized.
    if (WITH_SOUND) {
        if (!MIX_Init()) {
            SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO,
                        "SDL_Plotter: MIX_Init failed; sound disabled: %s",
                        SDL_GetError());
        } else {
            mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
                                           nullptr);

            if (mixer == nullptr) {
                SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO,
                            "SDL_Plotter: unable to open audio device; "
                            "sound disabled: %s",
                            SDL_GetError());
                MIX_Quit();
            } else {
                SOUND = true;
            }
        }
    }

    // Display the initial white drawing surface.
    update();
}

SDL_Plotter::~SDL_Plotter() {
    // Release each caller-owned MIX_Audio reference.  SDL3_mixer internally
    // reference-counts audio data, so an active playback may safely finish.
    for (std::map<std::string, param>::iterator it = soundMap.begin();
         it != soundMap.end();
         ++it) {
        if (it->second.audio != nullptr) {
            MIX_DestroyAudio(it->second.audio);
            it->second.audio = nullptr;
            it->second.running = false;
        }
    }
    soundMap.clear();

    // Destroy the mixer before shutting down SDL3_mixer.
    if (mixer != nullptr) {
        MIX_DestroyMixer(mixer);
        mixer = nullptr;
    }

    if (SOUND) {
        MIX_Quit();
        SOUND = false;
    }

    // Text input should be stopped before its window is destroyed.
    if (window != nullptr) {
        SDL_StopTextInput(window);
    }

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    // SDL_Plotter initialized only the video subsystem directly.  Using the
    // subsystem-specific shutdown call avoids globally terminating unrelated
    // SDL subsystems owned by other application components.
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

// -----------------------------------------------------------------------------
// Display operations
// -----------------------------------------------------------------------------

void SDL_Plotter::update() {
    // Copy the CPU-side pixel array to the SDL texture.  Pitch is the number of
    // bytes occupied by one complete row in the source buffer.
    if (!SDL_UpdateTexture(texture,
                           nullptr,
                           pixels.data(),
                           col * static_cast<int>(sizeof(Uint32)))) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER,
                     "SDL_Plotter: SDL_UpdateTexture failed: %s",
                     SDL_GetError());
        return;
    }

    // SDL3 rendering uses a backbuffer: clear it, copy the complete texture to
    // it, and then present the finished frame.
    if (!SDL_RenderClear(renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER,
                     "SDL_Plotter: SDL_RenderClear failed: %s",
                     SDL_GetError());
        return;
    }

    if (!SDL_RenderTexture(renderer, texture, nullptr, nullptr)) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER,
                     "SDL_Plotter: SDL_RenderTexture failed: %s",
                     SDL_GetError());
        return;
    }

    if (!SDL_RenderPresent(renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER,
                     "SDL_Plotter: SDL_RenderPresent failed: %s",
                     SDL_GetError());
    }
}

Uint32 SDL_Plotter::getColor(int x, int y) {
    // Coordinates are a documented precondition for this accessor so that its
    // behavior remains consistent with the original implementation.
    return pixels[static_cast<std::size_t>(y) *
                      static_cast<std::size_t>(col) +
                  static_cast<std::size_t>(x)];
}

void SDL_Plotter::plotPixel(int x, int y, int r, int g, int b) {
    // Ignore out-of-range coordinates rather than writing outside the pixel
    // buffer.  RGB values are expected to already be in the range [0, 255].
    if (x >= 0 && y >= 0 && x < col && y < row) {
        pixels[static_cast<std::size_t>(y) *
                   static_cast<std::size_t>(col) +
               static_cast<std::size_t>(x)] =
            static_cast<Uint32>(RED_SHIFT * r +
                                GREEN_SHIFT * g +
                                BLUE_SHIFT * b);
    }
}

void SDL_Plotter::plotPixel(point p, int r, int g, int b) {
    plotPixel(p.x, p.y, r, g, b);
}

void SDL_Plotter::plotPixel(int x, int y, color c) {
    plotPixel(x,
              y,
              static_cast<int>(c.R),
              static_cast<int>(c.G),
              static_cast<int>(c.B));
}

void SDL_Plotter::plotPixel(point p, color c) {
    plotPixel(p.x,
              p.y,
              static_cast<int>(c.R),
              static_cast<int>(c.G),
              static_cast<int>(c.B));
}

void SDL_Plotter::clear() {
    // OPAQUE_WHITE is 0xFFFFFFFF, the ARGB8888 representation produced by the
    // original byte-wise fill with WHITE (255).
    std::fill(pixels.begin(), pixels.end(), OPAQUE_WHITE);
}

int SDL_Plotter::getRow() {
    return row;
}

int SDL_Plotter::getCol() {
    return col;
}

// -----------------------------------------------------------------------------
// Event and keyboard handling
// -----------------------------------------------------------------------------

bool SDL_Plotter::getQuit() {
    // Consume all currently pending events so SDL's internal keyboard state and
    // this wrapper's queues remain current.
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_TEXT_INPUT) {
            const char key = getKeyPress(event);
            if (key != '\0') {
                key_queue.push(key);
            }
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            // Arrow keys do not arrive as printable text.  Preserve the legacy
            // SDL_Plotter numeric codes used by existing client programs.
            switch (event.key.scancode) {
                case SDL_SCANCODE_DOWN:
                    key_queue.push(DOWN_ARROW);
                    break;

                case SDL_SCANCODE_UP:
                    key_queue.push(UP_ARROW);
                    break;

                case SDL_SCANCODE_LEFT:
                    key_queue.push(LEFT_ARROW);
                    break;

                case SDL_SCANCODE_RIGHT:
                    key_queue.push(RIGHT_ARROW);
                    break;

                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                default:
                    break;
            }
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            // SDL3 stores event coordinates as floats.  SDL_Plotter's public
            // point type is integer-based, so truncate to integer coordinates.
            click_queue.push(point(static_cast<int>(event.button.x),
                                   static_cast<int>(event.button.y)));
        }

        if (event.type == SDL_EVENT_QUIT) {
            quit = true;
        }
    }

    return quit;
}

bool SDL_Plotter::kbhit() {
    return !key_queue.empty();
}

bool SDL_Plotter::mouseClick() {
    return !click_queue.empty();
}

char SDL_Plotter::getKeyPress(const SDL_Event& event) const {
    // SDL3 text input is UTF-8.  The historical interface returns one char, so
    // only the first byte can be returned without changing the public API.
    if (event.text.text == nullptr || event.text.text[0] == '\0') {
        return '\0';
    }

    return event.text.text[0];
}

char SDL_Plotter::getKey() {
    if (key_queue.empty()) {
        return '\0';
    }

    const char key = key_queue.front();
    key_queue.pop();
    return key;
}

point SDL_Plotter::getMouseClick() {
    if (click_queue.empty()) {
        return point();
    }

    const point p = click_queue.front();
    click_queue.pop();
    return p;
}

void SDL_Plotter::setQuit(bool flag) {
    quit = flag;
}

// -----------------------------------------------------------------------------
// SDL3_mixer sound handling
// -----------------------------------------------------------------------------

void SDL_Plotter::initSound(std::string sound) {
    if (!SOUND || mixer == nullptr) {
        return;
    }

    param& soundData = soundMap[sound];

    // Avoid loading the same audio file more than once while it remains active.
    if (soundData.running && soundData.audio != nullptr) {
        return;
    }

    soundData.name = sound;

    // predecode=true most closely matches the original Mix_LoadWAV behavior:
    // the short sound effect is prepared in memory for repeated playback.
    soundData.audio = MIX_LoadAudio(mixer, sound.c_str(), true);

    if (soundData.audio == nullptr) {
        soundData.running = false;
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO,
                     "SDL_Plotter: unable to load sound '%s': %s",
                     sound.c_str(),
                     SDL_GetError());
        return;
    }

    soundData.running = true;
}

void SDL_Plotter::playSound(std::string sound) {
    if (!SOUND || mixer == nullptr) {
        return;
    }

    std::map<std::string, param>::iterator it = soundMap.find(sound);
    if (it == soundMap.end() ||
        !it->second.running ||
        it->second.audio == nullptr) {
        return;
    }

    // MIX_PlayAudio is asynchronous "fire-and-forget" playback.  SDL3_mixer
    // manages the temporary playback track internally, eliminating the custom
    // thread/condition-variable mechanism required by the older implementation.
    if (!MIX_PlayAudio(mixer, it->second.audio)) {
        SDL_LogError(SDL_LOG_CATEGORY_AUDIO,
                     "SDL_Plotter: unable to play sound '%s': %s",
                     sound.c_str(),
                     SDL_GetError());
    }
}

void SDL_Plotter::quitSound(std::string sound) {
    std::map<std::string, param>::iterator it = soundMap.find(sound);
    if (it == soundMap.end()) {
        return;
    }

    if (it->second.audio != nullptr) {
        // MIX_Audio is internally reference-counted.  Releasing this reference
        // is safe even if a fire-and-forget playback is still using the audio.
        MIX_DestroyAudio(it->second.audio);
        it->second.audio = nullptr;
    }

    it->second.running = false;
}

// -----------------------------------------------------------------------------
// Timing and direct mouse-event helpers
// -----------------------------------------------------------------------------

void SDL_Plotter::Sleep(int ms) {
    // SDL_Delay accepts an unsigned duration.  Prevent a negative int from
    // becoming a very large delay after integer conversion.
    SDL_Delay(static_cast<Uint32>((ms < 0) ? 0 : ms));
}

bool SDL_Plotter::getMouseDown(int& x, int& y) {
    x = 0;
    y = 0;

    if (!SDL_PollEvent(&event)) {
        return false;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        x = static_cast<int>(event.button.x);
        y = static_cast<int>(event.button.y);
        return true;
    }

    // Preserve an unrelated event for subsequent processing.
    SDL_PushEvent(&event);
    return false;
}

bool SDL_Plotter::getMouseUp(int& x, int& y) {
    x = 0;
    y = 0;

    if (!SDL_PollEvent(&event)) {
        return false;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        x = static_cast<int>(event.button.x);
        y = static_cast<int>(event.button.y);
        return true;
    }

    SDL_PushEvent(&event);
    return false;
}

bool SDL_Plotter::getMouseMotion(int& x, int& y) {
    x = 0;
    y = 0;

    if (!SDL_PollEvent(&event)) {
        return false;
    }

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        x = static_cast<int>(event.motion.x);
        y = static_cast<int>(event.motion.y);
        return true;
    }

    SDL_PushEvent(&event);
    return false;
}

void SDL_Plotter::getMouseLocation(int& x, int& y) {
    float mouseX = 0.0f;
    float mouseY = 0.0f;

    SDL_GetMouseState(&mouseX, &mouseY);

    x = static_cast<int>(mouseX);
    y = static_cast<int>(mouseY);

    // Retained from the original SDL_Plotter behavior.
    std::cout << x << " " << y << std::endl;
}
