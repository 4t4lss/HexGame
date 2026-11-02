#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <unordered_map>
#include <string>

enum Player : char {NONE = 0b00, PLAYER1 = 0b01, PLAYER2 = 0b10};

struct Cell {
    int row;
    int col;

    Cell(const int row = -1, const int col = -1):
        row{row},
        col{col}
    {}

    bool operator==(const Cell& other) {
        return row == other.row && col == other.col;
    }
};


struct CellHasher {
    size_t operator()(const Cell& p) const
    {
        // Combine hashes of x and y using the bitwise XOR
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
