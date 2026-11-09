/*
* Author: Shawn Douglas
* Assignment Title: Hex Game
* Assignment Description: Defines TestInput class
* using cin, and tracks running state for post game
* moves
* Due Date: 11/13/2026
* Date Created: 10/23/2026
* Date Last Modified: 11/9/2026
*/

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
        * description: reads move data from test input
        *              into move object
        * return: Move
        * precondition: cin must contain input
        * postcondition: input data is read into Move object                
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

        /*
        * description: checks if the game is still running
        * for post game move validation
        * return: bool
        * precondition: none
        * postcondition: true is returned if the game
        * is running, false otherwise             
        * 
        */
        bool isRunning();
};
#endif
