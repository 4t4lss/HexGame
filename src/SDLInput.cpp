#include "SDLInput.h"
/*
 * description:
 * return: 
 * precondition:
 * postcondition:                                                   
 */
SDLInput::SDLInput (WindowManager* wm) {
}
/*
 * description:
 * return: 
 * precondition:
 * postcondition:                                                   
 */
SDLInput::~SDLInput() {
}
/*
 * description:
 * return: 
 * precondition:
 * postcondition:                                                   
 */
Move SDLInput::getMove() {
    int x, y, row, col;

    Move move;

    // call getMouseClick on SDL_Plotter object
    wm.getMouseClick(x, y);

    row = (2 * -2 - (2 * y - WINDOW_ROWS + 
          (WINDOW_COLS - 2 * x) / 
          (radius * SQRT_3))) / 4
    
    col = (2 * (WINDOW_COLS - 2 * x)) / (3 * radius) + row

    move.c.x = row;
    move.c.y = col;

    return move;
}
/*
 * description:
 * return: 
 * precondition:
 * postcondition:                                                   
 */
size_t SDLInput::getBoardSize() {
    return 0;
}
/*
 * description:
 * return: 
 * precondition:
 * postcondition:                                                   
 */
bool SDLInput::isRunning() {
    return true;
}
