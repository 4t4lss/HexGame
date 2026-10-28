#ifndef INPUT_INTERFACE
#define INPUT_INTERFACE

#include "GameObjects.h"

class InputInterface {
    public:
        virtual ~InputInterface() = 0;
        virtual size_t getBoardSize() = 0;
        virtual Move getMove() = 0;
};

#endif
