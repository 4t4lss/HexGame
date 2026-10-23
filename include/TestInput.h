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
        TestInput(std::string fileName);
        Cell getMove(Player p);
};

#endif
