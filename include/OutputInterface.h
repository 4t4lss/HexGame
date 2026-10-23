#ifndef OUTPUT_INTERFACE
#define OUTPUT_INTERFACE

#include "GameObjects.h"

class OutputInterface {
    public:
        virtual void output(Board board, Cell lastMove) = 0;
};

#endif
