#include "TestOutput.h"

TestOutput::TestOutput(std::ostream outStream) : out(outStream) {
}

TestOutput::~TestOutput() {
}

void TestOutput::output(GameLogic gl, Move lastValidMove, std::ostream& out) {
   out << "MOVE" << gl.getTurnNumber() << ": " << lastValidMove.valid
       << "TURN: " << lastValidMove.p
       << "WINNER: " << gl.getWinner()
       << "HASH: " << hashGameState(gl)
       << std::endl;
}