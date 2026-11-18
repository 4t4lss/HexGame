/*
 * Author: Brennan Ellis
 * Assignment Title: Window Manager
 * Assignment Description: A wrapper around SDL_Plotter that
 *  controls the variables that are shared between
 *  SDL_Input and SDL_Output classes
 * Due Date: 11/16/2026
 * Date Created: 11/16/2026
 * Date Last Modified: 11/16/2026
 */
#include "WindowManager.h"

WindowManager::WindowManager() : 
    SDL_Plotter(HEIGHT, WIDTH, false) {
        setQuit(false);
}

void WindowManager::newSize(size_t boardSize) {
    CELL_RADIUS = static_cast<size_t>(BOARD_SIZE_SCALE * WIDTH * 3/(5 * boardSize));
}
