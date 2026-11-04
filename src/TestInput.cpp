#include "TestInput.h"

TestInput::TestInput() {
}

TestInput::~TestInput() {
}

Move TestInput::getMove() {
    Move move;
    int row, col;
    int player;


    std::cin >> player >> row >> col;
    move.c = Cell(row,col);
    move.p = static_cast<Player>(player);

    //std::cout << "Player: " << player+0 << " at " << row << " " << col << std::endl;

    return move;
}

size_t TestInput::getBoardSize() {
    int size;

    std::cin >> size;

    return size;
}

