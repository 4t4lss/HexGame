#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <unordered_map>
#include <string>

enum Player : char {NONE = 0, PLAYER1 = 1, PLAYER2 = 2};

struct Cell {
    int row;
    int col;

    Cell(const int row = -1, const int col = -1):
        row{row},
        col{col}
    {}

    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }

    bool operator<(const Cell& other) const {
        return row * 19 + col < other.row * 19 + other.col;
    }
};


struct CellHasher {
    size_t operator()(const Cell& p) const
    {
        // Multiply row by the max board size and add the column
        return p.row * 19 + p.col;
    }
};

struct Move {
    Cell c;
    Player p;
    bool valid;
    std::string result;
};

typedef std::unordered_map<Cell,Player, CellHasher> Board;

#endif
