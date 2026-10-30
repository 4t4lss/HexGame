#include "GameLogic.h"

bool GameLogic::detectWin(Player p) {
    return false;
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
