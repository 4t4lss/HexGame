#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

/**
 * @file SDL_Plotter.h
 * @brief Declaration of a simple pixel-oriented graphics and sound wrapper
 *        implemented with SDL3 and SDL3_mixer.
 *
 * @author Dr. Booth
 * @version 4.0
 * @date 2026-08-29
 *
 * @details
 * SDL_Plotter provides a small, introductory interface for creating an SDL
 * window, drawing individual pixels, receiving keyboard and mouse input, and
 * playing short sound files.  The class intentionally hides most SDL details
 * so that client programs can concentrate on graphics and algorithmic logic.
 *
 * Version 4.0 migrates the implementation from SDL2/SDL2_mixer to
 * SDL3/SDL3_mixer.  The public SDL_Plotter interface is retained as closely as
 * possible so that existing programs require few, if any, source changes.
 *
 * Important SDL3 migration details:
 * - SDL headers now use the SDL3 and SDL3_mixer include directories.
 * - SDL3 text input must be enabled explicitly by the implementation.
 * - SDL3 mouse coordinates are floating point and are converted to int here
 *   to preserve the original SDL_Plotter interface.
 * - SDL3_mixer no longer uses Mix_Chunk/channel playback.  Sounds are stored as
 *   MIX_Audio objects and played through a MIX_Mixer.
 *
 * Required libraries:
 * - SDL3
 * - SDL3_mixer
 */

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <map>
#include <queue>
#include <string>
#include <vector>

// -----------------------------------------------------------------------------
// Legacy SDL_Plotter constants
// -----------------------------------------------------------------------------

/** Value returned by getKey() for the up-arrow key. */
const char UP_ARROW = 1;

/** Value returned by getKey() for the down-arrow key. */
const char DOWN_ARROW = 2;

/** Value returned by getKey() for the left-arrow key. */
const char LEFT_ARROW = 3;

/** Value returned by getKey() for the right-arrow key. */
const char RIGHT_ARROW = 4;

/** Multiplier used to place the red component in an ARGB8888 pixel. */
const int RED_SHIFT = 65536;

/** Multiplier used to place the green component in an ARGB8888 pixel. */
const int GREEN_SHIFT = 256;

/** Multiplier used to place the blue component in an ARGB8888 pixel. */
const int BLUE_SHIFT = 1;

/** Multiplier used to place the alpha component in an ARGB8888 pixel. */
const int ALPHA_SHIFT = 16777216;

/** Eight-bit value representing full intensity. */
const int WHITE = 255;

/**
 * Legacy constant retained for source compatibility.
 *
 * SDL3_mixer manages playback internally, so SDL_Plotter no longer creates a
 * pool of sound threads.
 */
const int MAX_THREAD = 100;

// -----------------------------------------------------------------------------
// Supporting data structures
// -----------------------------------------------------------------------------

/**
 * @struct point
 * @brief Stores an integer two-dimensional coordinate.
 */
struct point {
    int x;  ///< Horizontal coordinate.
    int y;  ///< Vertical coordinate.

    /**
     * @brief Constructs the point (0, 0).
     */
    point() : x(0), y(0) {}

    /**
     * @brief Constructs a point with caller-supplied coordinates.
     * @param xValue Horizontal coordinate.
     * @param yValue Vertical coordinate.
     */
    point(int xValue, int yValue) : x(xValue), y(yValue) {}
};

/**
 * @struct color
 * @brief Stores an RGB color using integer component values.
 *
 * Component values supplied to plotPixel() are expected to be in the range
 * [0, 255].
 */
struct color {
    unsigned int R;  ///< Red component.
    unsigned int G;  ///< Green component.
    unsigned int B;  ///< Blue component.

    /**
     * @brief Constructs black: (0, 0, 0).
     */
    color() : R(0), G(0), B(0) {}

    /**
     * @brief Constructs a color from red, green, and blue components.
     * @param r Red component in the range [0, 255].
     * @param g Green component in the range [0, 255].
     * @param b Blue component in the range [0, 255].
     */
    color(int r, int g, int b)
        : R(static_cast<unsigned int>(r)),
          G(static_cast<unsigned int>(g)),
          B(static_cast<unsigned int>(b)) {}
};

/**
 * @struct param
 * @brief Stores the SDL3_mixer resource associated with one named sound.
 *
 * @details
 * Earlier SDL2 versions of SDL_Plotter used this structure to coordinate a
 * dedicated sound thread.  SDL3_mixer provides asynchronous mixing directly,
 * so the structure now only records the loaded MIX_Audio object and its state.
 */
struct param {
    bool running;          ///< True when the sound has been loaded successfully.
    MIX_Audio* audio;      ///< Reusable SDL3_mixer audio object; nullptr if absent.
    std::string name;      ///< File name/path used to load the sound.

    /**
     * @brief Constructs an empty sound record.
     */
    param() : running(false), audio(nullptr), name() {}
};

// -----------------------------------------------------------------------------
// SDL_Plotter class
// -----------------------------------------------------------------------------

/**
 * @class SDL_Plotter
 * @brief Provides simple pixel graphics, keyboard/mouse input, and sound.
 *
 * @details
 * The class owns an SDL window, renderer, texture, and an in-memory ARGB8888
 * pixel buffer.  Calling plotPixel() changes the memory buffer; calling
 * update() copies that buffer to the SDL texture and presents it on screen.
 *
 * Keyboard and mouse events are processed through SDL's event queue.  Printable
 * text is stored in an internal character queue, while the four arrow keys are
 * represented by UP_ARROW, DOWN_ARROW, LEFT_ARROW, and RIGHT_ARROW.
 *
 * SDL_Plotter owns SDL resources and therefore cannot be copied.
 */
class SDL_Plotter {
private:
    SDL_Texture* texture;                 ///< Texture containing the pixel image.
    SDL_Renderer* renderer;               ///< SDL renderer associated with window.
    SDL_Window* window;                   ///< Application window.
    std::vector<Uint32> pixels;           ///< In-memory ARGB8888 pixel buffer.
    SDL_Event event;                      ///< Temporary event used while polling SDL.
    int row;                              ///< Height of the drawing area in pixels.
    int col;                              ///< Width of the drawing area in pixels.
    bool quit;                            ///< True when application termination requested.

    std::queue<char> key_queue;           ///< Pending keyboard characters/key codes.
    std::queue<point> click_queue;        ///< Pending mouse-button-release locations.

    bool SOUND;                           ///< True when SDL3_mixer is available for use.
    MIX_Mixer* mixer;                     ///< Mixer connected to the default audio device.
    std::map<std::string, param> soundMap;///< Loaded sounds indexed by file name/path.

    /**
     * @brief Converts an SDL text-input event to the legacy char representation.
     *
     * @param event SDL event whose type is SDL_EVENT_TEXT_INPUT.
     * @return First byte of the UTF-8 text sequence, or '\0' if no text exists.
     *
     * @note The historical SDL_Plotter interface returns char, so a complete
     *       multi-byte Unicode character cannot be represented by this method.
     */
    char getKeyPress(const SDL_Event& event) const;

public:
    /**
     * @brief Constructs and initializes an SDL3 plotting window.
     *
     * @param r Number of rows (window height). Must be greater than zero.
     * @param c Number of columns (window width). Must be greater than zero.
     * @param WITH_SOUND If true, attempt to initialize SDL3_mixer sound support.
     *
     * @throws std::invalid_argument if r or c is not positive.
     * @throws std::runtime_error if the SDL video subsystem, window, renderer,
     *         or texture cannot be created.
     *
     * Failure to initialize optional sound support does not prevent graphics
     * from operating; the error is reported through SDL's logging facility.
     */
    SDL_Plotter(int r = 480, int c = 640, bool WITH_SOUND = true);

    /**
     * @brief Releases all sound, texture, renderer, window, and SDL resources
     *        owned by this object.
     */
    ~SDL_Plotter();

    /** SDL_Plotter owns non-shareable SDL resources and cannot be copied. */
    SDL_Plotter(const SDL_Plotter&) = delete;

    /** SDL_Plotter owns non-shareable SDL resources and cannot be assigned. */
    SDL_Plotter& operator=(const SDL_Plotter&) = delete;

    /**
     * @brief Copies the current pixel buffer to the texture and displays it.
     */
    void update();

    /**
     * @brief Processes pending SDL events and reports whether execution should end.
     *
     * @return true if the window was closed, Escape was pressed, or setQuit(true)
     *         was called; otherwise false.
     */
    bool getQuit();

    /**
     * @brief Explicitly sets the internal quit flag.
     * @param flag New quit state.
     */
    void setQuit(bool flag);

    /**
     * @brief Reports whether a keyboard value is waiting in the input queue.
     * @return true when getKey() can retrieve a queued value.
     */
    bool kbhit();

    /**
     * @brief Reports whether a mouse click is waiting in the click queue.
     * @return true when getMouseClick() can retrieve a queued click.
     */
    bool mouseClick();

    /**
     * @brief Removes and returns the next queued keyboard value.
     * @return Next character/key code, or '\0' if the queue is empty.
     */
    char getKey();

    /**
     * @brief Removes and returns the next queued mouse click.
     * @return Click location, or point(0, 0) if the queue is empty.
     */
    point getMouseClick();

    /**
     * @brief Sets one pixel in the in-memory drawing buffer.
     * @param x Horizontal coordinate in [0, getCol()).
     * @param y Vertical coordinate in [0, getRow()).
     * @param r Red component in [0, 255].
     * @param g Green component in [0, 255].
     * @param b Blue component in [0, 255].
     *
     * Coordinates outside the drawing area are ignored.  The new pixel is not
     * visible until update() is called.
     */
    void plotPixel(int x, int y, int r, int g, int b);

    /**
     * @brief Sets one pixel using a point and separate RGB components.
     * @param p Pixel coordinate.
     * @param r Red component in [0, 255].
     * @param g Green component in [0, 255].
     * @param b Blue component in [0, 255].
     */
    void plotPixel(point p, int r, int g, int b);

    /**
     * @brief Sets one pixel using integer coordinates and a color object.
     * @param x Horizontal coordinate.
     * @param y Vertical coordinate.
     * @param c RGB color; defaults to black.
     */
    void plotPixel(int x, int y, color c = color{});

    /**
     * @brief Sets one pixel using a point and a color object.
     * @param p Pixel coordinate.
     * @param c RGB color; defaults to black.
     */
    void plotPixel(point p, color c = color{});

    /**
     * @brief Sets every pixel in the in-memory drawing buffer to white.
     *
     * The cleared image is not visible until update() is called.
     */
    void clear();

    /**
     * @brief Returns the drawing-area height.
     * @return Number of rows.
     */
    int getRow();

    /**
     * @brief Returns the drawing-area width.
     * @return Number of columns.
     */
    int getCol();

    /**
     * @brief Loads a sound file for subsequent playback.
     * @param sound File name/path of the audio file.
     *
     * Calling this function repeatedly for an already loaded sound has no
     * effect.  If sound support is unavailable or the file cannot be loaded,
     * the function returns without throwing and SDL records an error message.
     */
    void initSound(std::string sound);

    /**
     * @brief Starts asynchronous playback of a previously initialized sound.
     * @param sound File name/path originally supplied to initSound().
     */
    void playSound(std::string sound);

    /**
     * @brief Releases this object's reference to a previously loaded sound.
     * @param sound File name/path originally supplied to initSound().
     *
     * SDL3_mixer internally reference-counts MIX_Audio, so an already-playing
     * instance can safely finish even after this method releases the stored
     * object.
     */
    void quitSound(std::string sound);

    /**
     * @brief Suspends the calling thread for approximately ms milliseconds.
     * @param ms Delay duration in milliseconds. Negative values are treated as 0.
     */
    void Sleep(int ms);

    /**
     * @brief Checks the next SDL event for a mouse-button-down event.
     * @param x Receives the integer x coordinate when such an event is found.
     * @param y Receives the integer y coordinate when such an event is found.
     * @return true if a mouse-button-down event was retrieved; otherwise false.
     *
     * If the next event is a different type, it is pushed back onto SDL's event
     * queue so that other SDL_Plotter event processing can handle it.
     */
    bool getMouseDown(int& x, int& y);

    /**
     * @brief Checks the next SDL event for a mouse-button-up event.
     * @param x Receives the integer x coordinate when such an event is found.
     * @param y Receives the integer y coordinate when such an event is found.
     * @return true if a mouse-button-up event was retrieved; otherwise false.
     */
    bool getMouseUp(int& x, int& y);

    /**
     * @brief Checks the next SDL event for a mouse-motion event.
     * @param x Receives the integer x coordinate when such an event is found.
     * @param y Receives the integer y coordinate when such an event is found.
     * @return true if a mouse-motion event was retrieved; otherwise false.
     */
    bool getMouseMotion(int& x, int& y);

    /**
     * @brief Gets the current mouse position relative to the SDL window.
     * @param x Receives the integer x coordinate.
     * @param y Receives the integer y coordinate.
     *
     * @note For compatibility with the original implementation, the coordinates
     *       are also written to standard output.
     */
    void getMouseLocation(int& x, int& y);

    /**
     * @brief Returns the packed ARGB8888 value stored at a pixel coordinate.
     * @param x Horizontal coordinate. Must be within the drawing area.
     * @param y Vertical coordinate. Must be within the drawing area.
     * @return Packed 32-bit pixel value from the in-memory buffer.
     *
     * @pre 0 <= x < getCol() and 0 <= y < getRow().
     */
    Uint32 getColor(int x, int y);
};

#endif  // SDL_PLOTTER_H_
