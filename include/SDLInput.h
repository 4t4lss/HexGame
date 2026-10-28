#ifndef SDL_INPUT
#define SDL_INPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "InputInterface.h"

class SDLInput : public InputInterface {
    private:
        WindowManager wm;
    public:
        SDLInput (WindowManager& wm);
        ~SDLInput();
        Cell getMove(Player p);
        size_t getBoardSize();
};

#endif
