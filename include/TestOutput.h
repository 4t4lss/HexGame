#ifndef TEST_OUTPUT
#define TEST_OUTPUT

#include "GameObjects.h"
#include "OutputInterface.h"
#include "HashFunction.h"
#include <iostream>
#include <string>

class TestOutput : public OutputInterface {
    private:
    public:
        TestOutput();
        ~TestOutput();
        void output(GameLogic gl, Move lastValidMove);
};

#endif
