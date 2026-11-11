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
         * description: Enqueues all unvisited neighbors of the center cell
         *  that are owned by Player p
         * return: void
         * precondition: valid parameters are passed in
         * postcondition: none
        */
        void pushAdjacent(const Cell& center, std::queue<Cell>& list, std::set<Cell>& visited, const Player p);
        /*
         * description: detects whether player p has reached both ends of the 
         *  hex grid.
         * return: boolean
         * precondition: a valid GameLogic object has been instantiated, 
         *  a valid player has been passed.
         * postcondition: returns true if game has been won by player p.
        */
        bool detectWin(const Player p);
       
    public:
        /*
         * description: constructs a GameLogic object calling GameObject Board 
         * return: void
         * precondition: none
         * postcondition: none.
        */
        GameLogic(size_t boardSize);

        /*
         * description: Returns whether a given Move is valid or not.
         * return: boolean
         * precondition: a valid GameLogic object exists.
         * postcondition: returns true if move valid.
        */
        bool validateMove(Move& mov);

        /*
         * description: inserts Move into hashmap Board and runs win detection
         * return: void
         * precondition: The move passed has to be a valid move.
         * postcondition: Board now conatains Move, and the Game State is
         *  updated if the game is won
        */
        void writeMove(const Move& mov);

        /*
         * description: increments the turn counter and changes which player's
         *  turn it is.
         * return: void
         * precondition: A valid GameLogic object has been instantiated.
         * postcondition: turnNumber increments, currentPlayer alternates
        */
        void nextTurn();

        /*
         * description: returns the player whose current turn it is
         * return: Player
         * precondition: a GameLogic object has been instantiated
         * postcondition: none
        */
        Player getCurrentPlayer() const;

        /*
         * description: returns the winner of the game if there is one.
         * return: Player(NONE, PLAYER1, PLAYER2)
         * precondition: A GameLogic object has been instantiated.
         * postcondition: none
        */
        Player getWinner() const;

        /*
         * description: returns the Board object in its current state.
         * return: Board (unordered_map<Cell,Player>)
         * precondition: A valid board object exists.
         * postcondition: none
        */
        Board getBoard() const;

        /*
         * description: returns the size of the Board
         * return: size_t
         * precondition: a GameLogic object and a GameObject object have been
         *  instantiated with a valid board size. 
         * postcondition: none
        */
        size_t getBoardSize() const;

        /*
         * description: returns the turn number that the current game is on.
         * return: size_t
         * precondition: a valid BoardLogic object has been instantiated.
         * postcondition: none
         */
        size_t getTurnNumber() const;

        /*
         * description: returns the player associated at a row and cell
         * return: int: 1 for player 1, 2 for player 2, 0 for none
         * precondition: a row and column must be passed and a GameLogic
         *  object must be instantiated.
         * postcondition: none
        */
        int getCellOwner(int row, int col) const;

        /*
         * description: returns winner variable representing which player, if
         * any, has won the game
         * return: size_t, 0 for none, 1 for player1, 2 for player2
         * precondition: the GameLogic object exists
         * postcondition: none
        */
        size_t getGameStatus() const;


};

#endif
