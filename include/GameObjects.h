#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <map>
#include <string>

enum Player : char {NONE = 0b00, PLAYER1 = 0b01, PLAYER2 = 0b10};

struct Cell {
    int row;
    int col;

    Cell(const int row = -1, const int col = -1):
        row{row},
        col{col}
    {}
};

struct Move {
    Cell c;
    Player p;
    bool valid;
    std::string result;
};

typedef std::map<Cell,Player> Board;

#endif
