#ifndef SDL_OUTPUT
#define SDL_OUTPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "OutputInterface.h"

class SDLOutput : public OutputInterface {
    private:
        WindowManager wm;
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void drawCell(Cell c, Player p);
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        SDLOutput (WindowManager& wm);
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        ~SDLOutput();
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void output(Board board, Cell lastMove);
};

#endif
