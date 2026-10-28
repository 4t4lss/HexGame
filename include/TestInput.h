#ifndef TEST_INPUT
#define TEST_INPUT

#include "GameObjects.h"
#include "InputInterface.h"
#include <fstream>
#include <string>

class TestInput : public InputInterface {
    private:
        std::ifstream inFile;
    public:
        TestInput(const char* filename);
        ~TestInput();
        size_t getBoardSize();
        Move getMove();
};

#endif
