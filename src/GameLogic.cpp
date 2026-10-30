#include "GameLogic.h"

bool GameLogic::detectWin(Player p) {
    return false;
}

GameLogic::GameLogic(size_t boardSize):
    boardSize{boardSize},
    currentPlayer{PLAYER1},
    turnNumber{0},
    winner{NONE}
{}

bool GameLogic::writeMove(Move& mov) {

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
