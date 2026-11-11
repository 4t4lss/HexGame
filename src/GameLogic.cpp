#include "GameLogic.h"
#include <sstream>

void GameLogic::pushAdjacent(const Cell& center, std::queue<Cell>& list,
        std::set<Cell>& visited, const Player p) {
    int i = center.row, j = center.col;
    //Generates a list of all adjacent Cells
    Cell adj[] = {Cell(i+1, j+1), Cell(i+1, j), Cell(i, j+1),
        Cell(i, j-1), Cell(i-1, j), Cell(i-1, j-1)};

    //Checks Every Adjacent Cell
    for(Cell c : adj) {
        //If the Cell is in Bounds
        if(c.row >= 0 && c.row < boardSize && c.col >= 0 && c.col < boardSize
                /*And The Unordered Map Contains The Adjacent Cell
                 * with the correct player */
                && board.find(c) != board.end() && board.at(c) == p 
                // And the adjacent cell has not been visited
                & visited.count(c) == 0
          ) {
            list.push(c);
            visited.insert(c);
        }
    }
}

bool GameLogic::detectWin(const Player p) {
    bool win = false;
    //The game cannot be won in less than moves than the boardSize
    if(turnNumber/2 >= boardSize - 2) {
        std::set<Cell> visitedCells; //A set of all visitedCells
        std::queue<Cell> cellsToCheck; //A queue of cells to check in order
        for(size_t i = 0; i < boardSize; i++) {
            Cell cur;
            if(p == PLAYER1) {
                cur = Cell(0,i); 
                //Check cells along the first row for player 1
            }
            else {
                cur = Cell(i,0);
                //Check cells long the first column for player 2
            }
            if(board.find(cur) != board.end() && board.at(cur)==p) {
                //If the cell is owned by Player p, push it to the queue
                visitedCells.insert(cur);
                cellsToCheck.push(cur);
            }
        }
        //While a win has not been detected and there are cells left to check
        while(!win && !cellsToCheck.empty()) {
            /*Push all cells adjacent to the cell at the front of the queue
             * that are owned by Player p and have not been visited */
            pushAdjacent(cellsToCheck.front(), cellsToCheck, visitedCells, p);
            cellsToCheck.pop();
            if(!cellsToCheck.empty()) {
                if((p == PLAYER1 &&
                        //If Player 1, check if we're at the last row
                        cellsToCheck.front().row == boardSize-1) ||
                        p == PLAYER2 &&
                        //If Player 2, check if we're at the last col
                        cellsToCheck.front().col == boardSize-1) {
                    win = true;
                }
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
    //Check if out of bounds
    if(mov.c.row < 0 || mov.c.row >= boardSize ||
            mov.c.col < 0 || mov.c.col >= boardSize) {
        mov.valid = false;
        mov.result = "Out of Bounds";
    }
    //Check if the game is already won
    else if (winner != NONE){
        mov.valid = false;
        mov.result = "Game already won";
    }
    //If the move is not the correct player
    else if(mov.p != currentPlayer) {
        mov.valid = false;
        std::ostringstream oss;
        oss << "Invalid Player: " << static_cast<int>(mov.p)
            << " when should be " << static_cast<int>(currentPlayer);
        mov.result = oss.str();
    }
    //If the cell is already occupied, unless it's the first move (Swap Rule)
    else if (board.find(mov.c) != board.end() && getTurnNumber() != 1){
        mov.valid = false;
        mov.result = "Cell already taken";
    }
    //Accept the Move
    else {
        mov.valid = true;
        mov.result = "ACCEPTED";
        //Push Back the valid move
        validMoveHistory.push_back(mov);
    }


    return mov.valid;

}

void GameLogic::writeMove(const Move& mov) {
    board.emplace(mov.c, mov.p);

    if(detectWin(mov.p)) {
        //If the game is won, update the game state
        winner = mov.p;
        currentPlayer=NONE;
    }
}

void GameLogic::nextTurn() {
    turnNumber++;
    if(currentPlayer!=NONE) {
        //Swap the current Player
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
    Player owner = NONE;
    if(board.find(c) != board.end()) owner = board.at(c);
    return static_cast<int>(owner);
}

size_t GameLogic::getGameStatus() const {
    return winner;
}
