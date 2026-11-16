#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "GameObjects.h"
#include "SDL_Plotter.h"

const float SQRT_3 = 1.73205080757;

class WindowManager {
    public:
        SDL_Plotter g;
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
