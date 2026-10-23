#ifndef INPUT_INTERFACE
#define INPUT_INTERFACE

#include "GameObjects.h"

class InputInterface {
    public:
        virtual Cell getMove(Player p) = 0;
};

#endif
