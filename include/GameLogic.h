#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "GameObjects.h"
#include <map>

class GameLogic {
    private:
        size_t boardSize;
        Board board;
        Player currentPlayer;
        size_t turnNumber;
        
    public:
        GameLogic(size_t boardSize);

        bool writeMove(Cell c);

        bool detectWin(Player p);

        void nextTurn();

        Player getCurrentPlayer();

        Board getBoard();
};

#endif
