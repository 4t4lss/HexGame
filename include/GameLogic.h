#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "GameObjects.h"
#include <queue>
#include <set>

class GameLogic {
    private:
        size_t boardSize;
        Board board;
        Player currentPlayer;
        size_t turnNumber;
        Player winner;
        std::vector<Move> validMoveHistory;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void pushNeighbors(const Cell& center, std::queue<Cell>& list, std::set<Cell>& visited, const Player p);
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        bool detectWin(const Player p);
        
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        GameLogic(size_t boardSize);

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        bool validateMove(Move& mov);

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void writeMove(const Move& mov);

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void nextTurn();

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        Player getCurrentPlayer() const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        Player getWinner() const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        Board getBoard() const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        size_t getBoardSize() const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        size_t getTurnNumber() const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        int getCellOwner(int row, int col) const;

        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        size_t getGameStatus() const;


};

#endif
