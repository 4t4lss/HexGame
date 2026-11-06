/*
 * Author: Brennan Ellis
 * Assignment Title: Hex Game
 * Assignment Description: The main loop of the game. Controls passing
 *  information between the input, game logic, and output.
 * Due Date: 11/13/2026
 * Date Created: 10/23/2026
 * Date Last Modified: 11/06/2026
 */
#include "GameObjects.h"
#include "GameLogic.h"
#include "TestInput.h"
#include "TestOutput.h"
#include <cassert>

/*
 * Data Abstraction:
 * Instantiates the input and output classes. For Milestone 2, only
 * uses test input and output. Asserts that argc > 1 to test for "--test"
 *
 * Instantiates the board with a given size from the input.
 *  
 * Input: 
 * Gets the inputted move containing the Row, Column, and Player
 *  
 * Process:
 * Passes the inputted move into game logic to determine its validity. 
 * If the move is valid, write the move onto the game board.
 *  
 * Output: 
 * Output the move. Will output if the move is rejected or accepted,
 * the next player's turn, and the hash of the board.
 *  
 * Assumptions: 
 * Test Input files will begin with a single number dictating the size of the
 * board. Every row after that will contain 3 numbers representing the player,
 * the row, and the column of a move.
 */

int main(int argc, char* argv[]) {
	//Data Abstraction
    TestInput* input;
    TestOutput* output;
    //WindowManager* wm;
    assert(argc > 1);
    input = new TestInput();
    output = new TestOutput(std::cout);

    GameLogic game(input->getBoardSize());

    Move move;
    while(input->isRunning()) {
        //User Input
        move = input->getMove();
        
        //Data Processing
        if(game.validateMove(move)) {
            game.writeMove(move);
            game.nextTurn();
        }

        //Output
        output->output(game, move);
    }

    delete input;
    delete output;
    return 0;
}
