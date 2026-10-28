#include "TestInput.h"

TestInput::TestInput(const char* fileName) : inFile(fileName) {
}

TestInput::~TestInput() {
    inFile.close();
}

Move TestInput::getMove() {
    Move move;
    int row, col;
    int player;

    inFile >> player >> row >> col;
    move.c = Cell(row,col);
    move.p = static_cast<Player>(player);

    return move;
}

size_t TestInput::getBoardSize() {
    int size;

    inFile >> size;

    return size;
}

