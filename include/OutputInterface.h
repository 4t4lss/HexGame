#ifndef OUTPUT_INTERFACE
#define OUTPUT_INTERFACE

#include "GameObjects.h"
#include "GameLogic.h"

class OutputInterface {
    public:
        virtual ~OutputInterface() = 0;
        virtual void output(GameLogic gl, Move lastValidMove) = 0;
};

#endif
