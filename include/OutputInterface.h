#ifndef OUTPUT_INTERFACE
#define OUTPUT_INTERFACE

#include "GameObjects.h"
#include "GameLogic.h"

class OutputInterface {
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        virtual ~OutputInterface() = default;
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        virtual void output(GameLogic gl, Move lastValidMove) = 0;
};

#endif
