#include "GameLogic.h"
#include <sstream>

void GameLogic::pushNeighbors(const Cell& center, std::queue<Cell>& list, std::set<Cell>& visited, const Player p) {
    int i = center.row, j = center.col;
    Cell adj[] = {Cell(i+1, j+1), Cell(i+1, j), Cell(i, j+1), Cell(i, j-1), Cell(i-1, j), Cell(i-1, j-1)};

    for(Cell c : adj) {
        if(board.find(c) != board.end() && board.at(c) == p && visited.count(c) == 0
                && c.row >= 0 && c.row < boardSize && c.col >= 0 && c.col < boardSize) {
            list.push(c);
            visited.insert(c);
        }
    }
}

bool GameLogic::detectWin(const Player p) {
    bool win = false;
    if(turnNumber/2 >= boardSize - 2) {
        std::set<Cell> visitedCells;
        std::queue<Cell> cellsToCheck;
        for(size_t i = 0; i < boardSize; i++) {
            Cell cur;
            if(p == PLAYER1) {
                cur = Cell(0,i);
            }
            else {
                cur = Cell(i,0);
            }
            if(board.find(cur) != board.end() && board.at(cur)==p) {
                pushNeighbors(cur, cellsToCheck, visitedCells, p);
                visitedCells.insert(cur);
            }
        }
        while(!win && !cellsToCheck.empty()) {
            pushNeighbors(cellsToCheck.front(), cellsToCheck, visitedCells, p);
            cellsToCheck.pop();
            if(!cellsToCheck.empty()) {
                if(p == PLAYER1 && cellsToCheck.front().row == boardSize-1) win = true;
                else if(cellsToCheck.front().col == boardSize-1) win = true;
            }
        }
    }
    return win;
}

GameLogic::GameLogic(size_t boardSize):
    boardSize{boardSize},
    currentPlayer{PLAYER1},
    turnNumber{1}
{
    winner = NONE;
}

bool GameLogic::validateMove(Move& mov) {
    if(mov.c.row < 0 || mov.c.row >= boardSize ||
            mov.c.col < 0 || mov.c.col >= boardSize) {
        mov.valid = false;
        mov.result = "Out of Bounds";
    }
    else if (winner != NONE){
        mov.valid = false;
        mov.result = "Game already won";
    }
    else if(mov.p != currentPlayer) {
        mov.valid = false;
        std::ostringstream oss;
        oss << "Invalid Player: " << (0+mov.p) << " when should be " << (0 + currentPlayer);
        mov.result = oss.str();
    }
    else if (board.find(mov.c) != board.end() && getTurnNumber() != 1){
        mov.valid = false;
        mov.result = "Cell already taken";
    }
    else {
        mov.valid = true;
        mov.result = "ACCEPTED";
    }


    return mov.valid;

}

void GameLogic::writeMove(const Move& mov) {
    board.emplace(mov.c, mov.p);

    if(detectWin(mov.p)) {
        winner = mov.p;
        currentPlayer=NONE;
    }
}

void GameLogic::nextTurn() {
    turnNumber++;
    if(currentPlayer!=NONE) {
        currentPlayer = currentPlayer==PLAYER2?PLAYER1:PLAYER2;
    }
}

Player GameLogic::getWinner() const {
    return winner;
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
    int owner = NONE+0;
    if(board.find(c)  != board.end()) owner = board.at(c)+0;
    return owner;
}

size_t GameLogic::getGameStatus() const {
    return winner;
}
