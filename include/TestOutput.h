#ifndef TEST_OUTPUT
#define TEST_OUTPUT

#include "GameObjects.h"
#include "OutputInterface.h"
#include <fstream>
#include <string>

class TestOutput : public OutputInterface {
    private:
        std::ofstream outFile;
        size_t hash(Board b);
    public:
        TestOutput(std::string fileName);
        Cell getMove(Player p);
};

#endif
