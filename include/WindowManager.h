#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "GameObjects.h"
#include "SDL_Plotter.h"

class WindowManager {
    private:
        size_t WIDTH;
        size_t HEIGHT;
        size_t CELL_RADIUS;
        color PLAYER1COLOR;
        color PLAYER2COLOR;
        SDL_Plotter g;
        size_t BOARD_SIDE_PADDING;
        size_t BOARD_TOP_PADDING;
        size_t BOARD_BOTTOM_PADDING;

        
    public:
};

#endif
