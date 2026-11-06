#ifndef INPUT_INTERFACE
#define INPUT_INTERFACE

#include "GameObjects.h"

class InputInterface {
    public:
        /*
         * description: Destructor for the InputInterface class
         * return: N/A
         * precondition: The called object exists
         * postcondition: Called object has been destroyed and memory is freed
        */
        virtual ~InputInterface() = default;
        /*
         * description: Returns the size of the game board
         * return: size_t: length and width of the board
         * precondition: A board object exists
         * postcondition: No changes to objects
        */
        virtual size_t getBoardSize() = 0;
        /*
         * description: Gets the details of a player turn from the
         *          input source and creates a move object with the inputed
         *          active player and cell coordinates
         * return: Move object
         * precondition: none
         * postcondition: Created a move object initialized with the
         *          inputed turn data
        */
        virtual Move getMove() = 0;
        /*
         * description: Checks if the input source is still active, 
         *          Ignores the next input
         * return: boolean
         * precondition: none
         * postcondition: none
        */
        virtual bool isRunning() = 0;
};

#endif
