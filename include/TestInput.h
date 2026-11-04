#ifndef TEST_INPUT
#define TEST_INPUT

#include "GameObjects.h"
#include "InputInterface.h"
#include <iostream>
#include <cassert>

class TestInput : public InputInterface {
    private:
    public:
        /*
        * description: default constructor
        * return: none
        * precondition: none
        * postcondition: none           
        * 
        */
        TestInput();

        /*
        * description:  destructor
        * return: none
        * precondition: none
        * postcondition: object is destructed        
        * 
        */
        ~TestInput();

        /*
        * description: reads move from test input
        *              into cell object
        * return: Cell
        * precondition: cin must contain input
        * postcondition: input data is read into Cell object                
        * 
        */
        Move getMove();

        /*
        * description: reads the board size from test input
        * return: int
        * precondition: cin must contain input
        * postcondition: board size is read from input file              
        * 
        */
        size_t getBoardSize();

        bool isRunning();
};
#endif
