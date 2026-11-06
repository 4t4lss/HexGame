/*
* Author: Shawn Douglas
* Assignment Title: Hex Game
* Assignment Description: Defines TestOuput
* class using output stream
* Due Date: 11/13/2026
* Date Created: 10/23/2026
* Date Last Modified: 11/6/2026
*/

#ifndef TEST_OUTPUT
#define TEST_OUTPUT

#include "GameObjects.h"
#include "OutputInterface.h"
#include "HashFunction.h"
#include <iostream>
#include <string>

class TestOutput : public OutputInterface {
    private:
        std::ostream& out;
        size_t moveCount;
    public:
        /*
        * description: paramtrized constructor
        * return: none
        * precondition: none
        * postcondition: TestOutput object is constructed
        *                with initialized output stream                     
        * 
        */
        TestOutput(std::ostream& out);

        /*
        * description: destructor
        * return: none
        * precondition: none
        * postcondition: object is destructed                   
        * 
        */
        ~TestOutput();

        /*
        * description: outputs test case results in 
        *              specified format
        * return: void
        * precondition: input data is processed, and object
        *               exists
        * postcondition: results for test case is outputted to 
        *                output stream                 
        * 
        */
        void output(GameLogic gl, Move lastValidMove);
};

#endif
