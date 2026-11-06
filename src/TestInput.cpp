/*
* Author: Shawn Douglas
* Assignment Title: Hex Game
* Assignment Description: implements TestInput
* member functions
* Due Date: 11/13/2026
* Date Created: 10/23/2026
* Date Last Modified: 11/6/2026
*/

#include "TestInput.h"

TestInput::TestInput() {
}

TestInput::~TestInput() {
}

Move TestInput::getMove() {
    Move move;
    int row, col;
    int player;

    // input text in player row column format
    std::cin >> player >> row >> col;

    // initialize cell object with input data
    move.c = Cell(row,col);
    move.p = static_cast<Player>(player);

    return move;
}

size_t TestInput::getBoardSize() {
    int size;

    // input the size from the the top of the cin
    std::cin >> size;

    return size;
}

bool TestInput::isRunning() {
    // return if the game is still running
    // for post game move validation
    return !(std::cin.eof());
}

