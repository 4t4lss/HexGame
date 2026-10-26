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
        ~TestInput();
        Cell getMove(Player p);
        int getBoardSize();
};

TestInput::TestInput(std::string fileName) : inFile(filename) {

}

TestInput::~TestInput() {
    inFile.close();
}

Cell TestInput::getMove(Player p) {
    int x, y;

    inFile >> p >> x >> y;

    return Cell(x, y);
}

int TestInput::getBoardSize() {
    int size;

    inFile >> size;

    return size;
}

#endif
