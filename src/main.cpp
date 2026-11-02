#include "GameObjects.h"
#include "GameLogic.h"
#include "TestInput.h"
#include "TestOutput.h"
#include <cassert>

// -----------------------------------------------------------------------------
// Program constants
// -----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    InputInterface* input;
    OutputInterface* output;
    //WindowManager* wm;
    assert(argc > 1);
    input = new TestInput(argv[1]);
    output = new TestOutput(std::cout);

    GameLogic game(input->getBoardSize());

    while(game.getWinner() == NONE) {
        Move move;
        do {
            move = input->getMove();
        } while(!game.writeMove(move));

        output->output(game, move);
    }

    delete input;
    delete output;
    return 0;
}
