#ifndef INPUT_INTERFACE
#define INPUT_INTERFACE

#include "GameObjects.h"

class InputInterface {
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        virtual ~InputInterface() = default;
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        virtual size_t getBoardSize() = 0;
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        virtual Move getMove() = 0;
        virtual bool isRunning() = 0;
};

#endif
