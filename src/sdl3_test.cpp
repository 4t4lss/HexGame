#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialization failed: "
                  << SDL_GetError() << '\n';
        return 1;
    }
    SDL_Window* window =
        SDL_CreateWindow("SDL3 Installation Test", 640, 480, 0);
    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    bool running = true;
    int result = 0;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        if (!running) break;
        if (!SDL_SetRenderDrawColor(renderer, 20, 80, 140, 255) ||
            !SDL_RenderClear(renderer) || !SDL_RenderPresent(renderer)) {
            std::cerr << "Rendering failed: " << SDL_GetError() << '\n';
            result = 1;
            break;
        }
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return result;
}
