#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <map>

enum Player : char {none = 0b00, PLAYER1 = 0b01, PLAYER2 = 0b10};

struct Cell {
    int x;
    int y;

    Cell(const int x = -1, const int y = -1):
        x{x},
        y{y}
    {}
};

typedef std::map<Cell,Player> Board;

#endif
