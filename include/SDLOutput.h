#ifndef SDL_OUTPUT
#define SDL_OUTPUT

#include "SDL_Plotter.h"
#include "GameObjects.h"
#include "OutputInterface.h"

class SDLOutput : public OutputInterface {
    private:
        SDL_Plotter g;
        void drawCell(Cell c, Player p);
    public:
        SDLOutput (SDL_Plotter& g);
        void output(Board board, Cell lastMove);
};

#endif
