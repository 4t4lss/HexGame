#ifndef SDL_OUTPUT
#define SDL_OUTPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "OutputInterface.h"

class SDLOutput : public OutputInterface {
    private:
        WindowManager wm;
        void drawCell(Cell c, Player p);
    public:
        SDLOutput (WindowManager& wm);
        ~SDLOutput();
        void output(Board board, Cell lastMove);
};

#endif
