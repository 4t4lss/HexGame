#include "TestOutput.h"

TestOutput::TestOutput(std::ostream& outStream) : out(outStream), moveCount{0} {
}

TestOutput::~TestOutput() {
}

void TestOutput::output(GameLogic gl, Move lastValidMove) {
    moveCount++;
    out << "MOVE " << moveCount << ": " << (lastValidMove.valid? "ACCEPTED" : "REJECTED") << std::endl
        << "TURN: " << static_cast<int>(gl.getCurrentPlayer()) << std::endl;
    if(gl.getWinner() == NONE) {
        out << "WINNER: none" <<std::endl;
    }
    else {
        out << "WINNER: " << static_cast<int>(gl.getWinner()) << std::endl;
    }
    out << "HASH: " << hashGameState(gl) << std::endl;
}
