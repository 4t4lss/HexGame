#include "SDL_Plotter.h"
#include "GameObjects.h"
#include "GameLogic.h"
#include "InputInterface.h"
#include "OutputInterface.h"
#include "TestInput.h"
#include "TestOutput.h"
#include "SDLInput.h"
#include "SDLOutput.h"

// -----------------------------------------------------------------------------
// Program constants
// -----------------------------------------------------------------------------

/** Height of the demonstration window in pixels. */
const int WINDOW_ROWS = 600;
/** Width of the demonstration window in pixels. */
const int WINDOW_COLS = 800;
/** Delay between loop iterations
 * when detecting inputs, in milliseconds. */
const int LOOP_DELAY = 10;

int main(int argc, char* argv[]) {
    const InputInterface& input = TestInput("testin.txt");
    const OutputInterface& output = TestOutput("testout.txt");

    GameLogic game(input.getBoardSize());

    while(!game.detectWin(PLAYER1) && !game.detectWin(PLAYER2)) {
        Cell move;
        do {
            move = input.getCell(game.getCurrentPlayer());
        } while(game.writeMove(move));

        output.output(game.getBoard(), move);

        game.nextTurn();
    }
}
