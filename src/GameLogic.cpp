#include "GameLogic.h"

void GameLogic::pushNeighbors(const Cell& center, std::queue<Cell>& list, std::set<Cell> visited, const Player p) {
    int i = center.row, j = center.col;
    Cell adj[] = {Cell(i+1, j+1), Cell(i+1, j), Cell(i, j+1), Cell(i, j-1), Cell(i-1, j), Cell(i-1, j-1)};

    for(Cell c : adj) {
        if(board.at(c) == p && visited.count(c) == 0) {
            list.push(c);
        }
    }
    visited.insert(center);
}

bool GameLogic::detectWin(Player p) {
    std::set<Cell> visitedCells;
    std::queue<Cell> neighborsToCheck;
    for(size_t i = 0; i < boardSize; i++) {
        Cell cur;
        if(p == PLAYER1) {
            cur = Cell(0,i);
        }
        else {
            cur = Cell(i,0);
        }
        if(board.at(cur)==p) {
            pushNeighbors(cur, neighborsToCheck, visitedCells, p);
        }
    }
    bool win = false;
    while(!win && !neighborsToCheck.empty()) {
        pushNeighbors(neighborsToCheck.front(), neighborsToCheck, visitedCells, p);
        neighborsToCheck.pop();
        if(p == PLAYER1 && neighborsToCheck.front().col == boardSize-1) win = true;
        else if(neighborsToCheck.front().row == boardSize-1) win = true;
    }
    return win;
}

GameLogic::GameLogic(size_t boardSize):
    boardSize{boardSize},
    currentPlayer{PLAYER1},
    turnNumber{1},
    winner{NONE}
{}

bool GameLogic::writeMove(Move& mov) {
    if(mov.c.row < 0 || mov.c.row >= boardSize ||
            mov.c.col < 0 || mov.c.col >= boardSize) {
        mov.valid = false;
        mov.result = "Out of Bounds";
    }
    else if (board.find(mov.c) == board.end() && getTurnNumber() != 1){
        mov.valid = false;
        mov.result = "Cell already taken";
    }
    else {
        mov.valid = true;
        mov.result = "ACCEPTED";

        board.emplace(mov.c, getCurrentPlayer());
    }


    return mov.valid;

}

Player GameLogic::getWinner() const {
    return currentPlayer;
}

Player GameLogic::getCurrentPlayer() const {
    return currentPlayer;
}

Board GameLogic::getBoard() const {
    return board;
}

size_t GameLogic::getBoardSize() const {
    return boardSize;
}

size_t GameLogic::getTurnNumber() const {
    return turnNumber;
}

int GameLogic::getCellOwner(int row, int col) const {
    Cell c(row,col);
    return board.at(c);
}

size_t GameLogic::getGameStatus() const {
    return winner;
}
