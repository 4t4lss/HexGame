#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "GameObjects.h"
#include "SDL_Plotter.h"

class WindowManager {
    private:
        SDL_Plotter g;
        size_t WIDTH;
        size_t HEIGHT;
        size_t CELL_RADIUS;
        color PLAYER1_COLOR;
        color PLAYER2_COLOR;
        float BOARD_SIZE_SCALE;
        size_t BOARD_VERTICAL_SHIFT;

    public:
};

#endif
