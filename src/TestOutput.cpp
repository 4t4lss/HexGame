/*
* Author: Shawn Douglas
* Assignment Title: Hex Game
* Assignment Description: Implements TestOutput
* member functions
* Due Date: 11/13/2026
* Date Created: 11/6/2026
* Date Last Modified: 11/6/2026
*/

#include "TestOutput.h"

TestOutput::TestOutput(std::ostream& outStream) : out(outStream), moveCount{0} {
}

TestOutput::~TestOutput() {
}

void TestOutput::output(GameLogic gl, Move lastMove) {
    // increment move count
    moveCount++;

    // ouput move details after processing
    out << "MOVE " << moveCount << ": " << (lastMove.valid? "ACCEPTED" : "REJECTED") << std::endl;
    out << "TURN: " << static_cast<int>(gl.getCurrentPlayer()) << std::endl;

    // output winner on each move
    if(gl.getWinner() == NONE) {
        out << "WINNER: none" <<std::endl;
    }
    else {
        out << "WINNER: " << static_cast<int>(gl.getWinner()) << std::endl;
    }
    out << "HASH: " << hashGameState(gl) << std::endl;
}
