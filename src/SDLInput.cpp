#include "SDLInput.h"
#include <iostream>

SDLInput::SDLInput (WindowManager* wm) : wm(wm) {
}

SDLInput::~SDLInput() {
}

bool SDLInput::getMove(Move& move) {
    bool moveExists = wm->mouseClick();

    if(moveExists){
        int row, col;

        // store board size for coordinate conversion
        size_t size = wm->BOARD_SIZE;
        point click = wm->getMouseClick();
        row = (-SQRT_3*wm->HEIGHT - wm->WIDTH + 2 * click.x + 2 * SQRT_3 * click.y) /
            (6 * wm->CELL_RADIUS) + (size-1)/2 + 0.5;
        col = (-SQRT_3*wm->HEIGHT + wm->WIDTH - 2 * click.x + 2 * SQRT_3 * click.y) /
            (6 * wm->CELL_RADIUS) + (size-1)/2 + 0.5;

        move.c.col = col;
        move.c.row = row;
    }
    move.valid = moveExists;

    return moveExists;
}

size_t SDLInput::getBoardSize() {
    size_t TEST_SIZE;
    std::cout << "Enter board size: " << std::flush;
    std::cin >> TEST_SIZE;
    wm->newSize(TEST_SIZE);

    return TEST_SIZE;
}

bool SDLInput::isRunning() {
    return !wm->getQuit();
}
