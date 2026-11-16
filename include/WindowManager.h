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

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "GameObjects.h"
#include "SDL_Plotter.h"

const float SQRT_3 = 1.73205080757;

class WindowManager : public SDL_Plotter {

    public:
        const size_t WIDTH = 900;
        const size_t HEIGHT = 900;
        const color PLAYER1_COLOR(255, 0, 0);
        const color PLAYER2_COLOR(0,0,255);
        const color BACKGROUND_COLOR(255,255,255);
        const float BOARD_SIZE_SCALE = 0.9;
        const size_t BOARD_VERTICAL_SHIFT  = 0;;
        size_t CELL_RADIUS;

        WindowManager(size_t boardSize);
        ~WindowManager();

        void newSize(size_t boardSize);
};

#endif
