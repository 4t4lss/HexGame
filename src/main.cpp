#include "GameObjects.h"
#include "GameLogic.h"
#include "TestInput.h"
#include "TestOutput.h"
#include <cassert>

// -----------------------------------------------------------------------------
// Program constants
// -----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    TestInput* input;
    TestOutput* output;
    //WindowManager* wm;
    assert(argc > 1);
    input = new TestInput(argv[1]);
    output = new TestOutput(std::cout);

    GameLogic game(input->getBoardSize());
    game.nextTurn();

    Move move;
    while(game.getWinner() == NONE) {

        move = input->getMove();
        game.validateMove(move);
        game.writeMove(move);
        output->output(game, move);
        game.nextTurn();

    }

    delete input;
    delete output;
    return 0;
}
