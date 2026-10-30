#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "GameObjects.h"
#include <vector>

class GameLogic {
    private:
        size_t boardSize;
        Board board;
        Player currentPlayer;
        size_t turnNumber;
        Player winner;
        std::vector<Move> validMoveHistory;

        bool detectWin(Player p);
        
    public:
        GameLogic(size_t boardSize);

        bool writeMove(Move& mov);

        Player getCurrentPlayer() const;

        Player getWinner() const;

        Board getBoard() const;

        size_t getBoardSize() const;

        size_t getTurnNumber() const;

        int getCellOwner(int row, int col) const;

        size_t getGameStatus() const;


};

#endif
