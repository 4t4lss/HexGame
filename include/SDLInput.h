#ifndef SDL_INPUT
#define SDL_INPUT

#include "SDL_Plotter.h"
#include "GameObjects.h"
#include "InputInterface.h"

class SDLInput : public InputInterface {
    private:
        SDL_Plotter g;
    public:
        SDLInput (SDL_Plotter& g);
        Cell getMove(Player p);
};

#endif
