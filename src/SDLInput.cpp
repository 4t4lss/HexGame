#include "SDLInput.h"
#include <iostream>

SDLInput::SDLInput (WindowManager* wm) : wm(wm) {
}

SDLInput::~SDLInput() {
}

Move SDLInput::getMove() {
    int row, col;

    // store board size for coordinate conversion
    size_t size = wm->BOARD_SIZE;

    // instantiate move object
    Move move;

    while(isRunning() && !wm->mouseClick()){
        wm->Sleep(wm->MSPF);
    }
    point click = wm->getMouseClick();
    row = -(SQRT_3*wm->HEIGHT + wm->WIDTH - 2 * click.x - 2 * SQRT_3 * click.y) /
        (6 * wm->CELL_RADIUS) + (size-1)/2 + 0.5;
    col = -(SQRT_3*wm->HEIGHT - wm->WIDTH + 2 * click.x - 2 * SQRT_3 * click.y) /
        (6 * wm->CELL_RADIUS) + (size-1)/2 + 0.5;

    move.c.col = col;
    move.c.row = row;
    std::cout << "\n(" << click.x << "," << click.y << ") -> (" << move.c.row << "," << move.c.col << ")" << std::endl;

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
