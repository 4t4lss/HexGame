#include "TestOutput.h"

TestOutput::TestOutput(std::ostream& outStream) : out(outStream) {
}

TestOutput::~TestOutput() {
}

void TestOutput::output(GameLogic gl, Move lastValidMove) {
    out << "MOVE " << gl.getTurnNumber() << ": " << (lastValidMove.valid? "ACCEPTED" : "REJECTED") << std::endl
        << "TURN: " << 0+lastValidMove.p << std::endl;
    if(gl.getWinner() == NONE) {
        out << "WINNER: none" <<std::endl;
    }
    else {
        out << "WINNER: " << static_cast<int>(gl.getWinner()) << std::endl;
    }
    out << "HASH: " << hashGameState(gl) << std::endl
        << std::endl;
}
