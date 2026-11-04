#include "TestOutput.h"

TestOutput::TestOutput(std::ostream& outStream) : out(outStream), moveCount{0} {
}

TestOutput::~TestOutput() {
}

void TestOutput::output(GameLogic gl, Move lastMove) {
    moveCount++;
    out << "MOVE " << moveCount << ": " << (lastMove.valid? "ACCEPTED" : "REJECTED") << std::endl;
    //if(!lastMove.valid) out << "REASON: " << lastMove.result << std::endl;
    out << "TURN: " << static_cast<int>(gl.getCurrentPlayer()) << std::endl;
    if(gl.getWinner() == NONE) {
        out << "WINNER: none" <<std::endl;
    }
    else {
        out << "WINNER: " << static_cast<int>(gl.getWinner()) << std::endl;
    }
    out << "HASH: " << hashGameState(gl) << std::endl;
}
