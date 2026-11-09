#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <unordered_map>
#include <string>

enum Player : char {NONE = 0, PLAYER1 = 1, PLAYER2 = 2};

struct Cell {
    int row;
    int col;

/*
 * description: Cell constructor
 * precondition: none
 * postcondition: row and col will contain the values passed in
 */
    Cell(const int row = -1, const int col = -1):
        row{row},
        col{col}
    {}

/*
 * description: Equality Operator
 * return: bool: true if the rows and columns are both equal
 * precondition: other is valid
 * postcondition: none
 */
    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }

/*
 * description: Less than Operator
 * return: bool: true if this's cordinates is less than other in
 *  row major order
 * precondition: other is valid
 * postcondition: none
 */
    bool operator<(const Cell& other) const {
        return row * 19 + col < other.row * 19 + other.col;
    }
};


struct CellHasher {
/*
 * description: Hashes the Cell's Cordinates
 * return: size_t: the hashed value
 * precondition: p is valid
 * postcondition: none
 */
    size_t operator()(const Cell& p) const
    {
        /* Multiply row by the max board size and add the column
        to get a unique row major index */
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
