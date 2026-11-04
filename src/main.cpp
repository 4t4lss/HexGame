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
    input = new TestInput();
    output = new TestOutput(std::cout);

    GameLogic game(input->getBoardSize());

    Move move;
    while(input->isRunning()) {
        std::cout << "Test" << std::endl;

        move = input->getMove();
        
        if(game.validateMove(move)) {
            game.writeMove(move);
            game.nextTurn();
        }


        output->output(game, move);
    }

    delete input;
    delete output;
    return 0;
}
