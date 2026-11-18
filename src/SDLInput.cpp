#include "SDLInput.h"

SDLInput::SDLInput (WindowManager* wm) : wm(wm) {
}

SDLInput::~SDLInput() {
}

Move SDLInput::getMove() {
    int x, y, row, col;

    // store board size for coordinate conversion
    size_t size = wm->boardSize;

    // instantiate move object
    Move move;

    // ***CALL MOUSE CLICK HELPER HERE***
    // temporary
    wm->getMouseClick(x, y);

    // convert raw click coordinates to board coordinates
    row = (2 * size - 2 - (2 * y - wm->HEIGHT + (wm->WIDTH - 2 * x) / 
          (wm->CELL_RADIUS * SQRT_3))) / 4;
    
    col = (2 * (wm->WIDTH - 2 * x)) / (3 * wm->CELL_RADIUS) + row;

    // convert coordinates to be at center of move's cell member
    move.c.row = row;
    move.c.col = col;

    return move;
}

size_t SDLInput::getBoardSize() {
    return wm->boardSize;
}

bool SDLInput::isRunning() {
    return true;
}
