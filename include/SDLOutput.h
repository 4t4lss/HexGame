#ifndef SDL_OUTPUT
#define SDL_OUTPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "OutputInterface.h"
#include <cmath>

#define PI = 3.1415926535

class SDLOutput : public OutputInterface {
    private:
        WindowManager* wm;
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        void drawCell(Cell c, Player p);
        void drawLine(SDL_Plotter& plotter, point pos1, point pos2, color color, int size);
        void drawHexagon(SDL_Plotter& plotter, point pos, color color, color fillColor, int radius);
        void fillHexagon(SDL_Plotter& plotter, color color, point pos, int radius);
    public:
        /*
         * description:
         * return: 
         * precondition:
         * postcondition:                                                   
        */
        SDLOutput (WindowManager* wm);
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
        void output(GameLogic gl, Move lastValidMove);
};

#endif
