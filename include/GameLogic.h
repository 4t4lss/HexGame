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

        void pushNeighbors(const Cell& center, std::queue<Cell>& list, std::set<Cell>& visited, const Player p);
        bool detectWin(const Player p);
        
    public:
        GameLogic(size_t boardSize);

        bool validateMove(Move& mov);

        void writeMove(const Move& mov);

        void nextTurn();

        Player getCurrentPlayer() const;

        Player getWinner() const;

        Board getBoard() const;

        size_t getBoardSize() const;

        size_t getTurnNumber() const;

        int getCellOwner(int row, int col) const;

        size_t getGameStatus() const;


};

#endif
