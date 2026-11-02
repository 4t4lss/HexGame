#include "TestInput.h"
#include <iostream>

TestInput::TestInput(const char* fileName) : inFile(fileName) {
}

TestInput::~TestInput() {
    inFile.close();
}

Move TestInput::getMove() {
    std::cout << "In getMove\n";
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
    // std::cout << "\n TestInput size: " << size;

    return size;
}

