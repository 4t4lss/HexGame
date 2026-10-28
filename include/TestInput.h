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
        /*
        * description: default constructor
        * return: none
        * precondition: none
        * postcondition: filestream object for input
        *                is opened              
        * 
        */
        TestInput(std::string fileName);

        /*
        * description:  destructor
        * return: none
        * precondition: none
        * postcondition: filestream object is closed        
        * 
        */
        ~TestInput();

        /*
        * description: reads move from test input
        *              into cell object
        * return: Cell
        * precondition: input file must be opened
        * postcondition: input data is read into Cell object                
        * 
        */
        Cell getMove(Player p);

        /*
        * description: reads the board size from test input
        * return: int
        * precondition: input file must be opened
        * postcondition: board size is read from input file              
        * 
        */
        int getBoardSize();
};

TestInput::TestInput(std::string fileName) : inFile(filename) {

}

TestInput::~TestInput() {
    inFile.close();
}

Cell TestInput::getMove(Player p) {
    int row, col;

    inFile >> p >> row >> col;

    return Cell(row, col);
}

int TestInput::getBoardSize() {
    int size;

    inFile >> size;

    return size;
}

#endif
