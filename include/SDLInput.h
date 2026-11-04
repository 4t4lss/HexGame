#ifndef SDL_INPUT
#define SDL_INPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "InputInterface.h"

class SDLInput : public InputInterface {
    private:
        WindowManager wm;
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        SDLInput (WindowManager& wm);
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        ~SDLInput();
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        Cell getMove(Player p);
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        size_t getBoardSize();
        bool isRunning();
};

#endif
