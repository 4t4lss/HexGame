#include "SDLInput.h"
#include <iostream>

SDLInput::SDLInput (WindowManager* wm) : wm(wm) {
}

SDLInput::~SDLInput() {
}

Move SDLInput::getMove() {
    int x, y;
    float row, col;

    // store board size for coordinate conversion
    size_t size = wm->BOARD_SIZE;
    
    // instantiate move object
    Move move;

    if(wm->mouseClick()){
        point click{wm->getMouseClick()};

        row = (2 * size - 2 - (2 * click.y - wm->HEIGHT + (wm->WIDTH - 2 * click.x) / 
              (wm->CELL_RADIUS * SQRT_3))) / 4;
        
        col = (2 * (wm->WIDTH - 2 * click.x)) / (3.0 * wm->CELL_RADIUS) + row;

        move.c.col = col;
        move.c.row = row;
    }
    std::cout << move.c.col << '\n' << move.c.row << '\n';

    return move;
}

size_t SDLInput::getBoardSize() {
    const size_t TEST_SIZE = 7;
    wm->newSize(TEST_SIZE);

    return TEST_SIZE;
}

bool SDLInput::isRunning() {
    return !wm->getQuit();
}
