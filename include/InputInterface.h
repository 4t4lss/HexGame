#ifndef INPUT_INTERFACE
#define INPUT_INTERFACE

#include "GameObjects.h"

class InputInterface {
    public:
        virtual ~InputInterface() = default;
        virtual size_t getBoardSize() = 0;
        virtual Move getMove() = 0;
};

#endif
