#ifndef OUTPUT_INTERFACE
#define OUTPUT_INTERFACE

#include "GameObjects.h"
#include "GameLogic.h"

class OutputInterface {
    public:
        /*
         * description: Destructor for the OutputInterface class
         * return: N/A
         * precondition: The called object exists
         * postcondition: Called object has been destroyed and memory is freed
        */
        virtual ~OutputInterface() = default;
        /*
         * description: Outputs the results of the last valid move in the
         *             active Output (SDL or Test) mode
         * return: void
         * precondition: Input data has been processed into a move object
         *              The game exists
         * postcondition: The results of the turn have been outputted to
         *             the active Output mode
        */
        virtual void output(GameLogic gl, Move lastValidMove) = 0;
};

#endif
