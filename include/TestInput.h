#ifndef TEST_INPUT
#define TEST_INPUT

#include "GameObjects.h"
#include "InputInterface.h"
#include <fstream>

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
        TestInput(const char* filename);

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
        Move getMove();

        /*
        * description: reads the board size from test input
        * return: int
        * precondition: input file must be opened
        * postcondition: board size is read from input file              
        * 
        */
        size_t getBoardSize();
};
#endif
