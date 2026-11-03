#include "TestInput.h"

TestInput::TestInput(const char* fileName) : inFile(fileName) {
    assert(inFile);
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

    //std::cout << "Player: " << player+0 << " at " << row << " " << col << std::endl;
    
    assert(!inFile.eof());

    return move;
}

size_t TestInput::getBoardSize() {
    int size;

    inFile >> size;

    return size;
}

