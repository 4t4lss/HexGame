#ifndef SDL_OUTPUT
#define SDL_OUTPUT

#include "WindowManager.h"
#include "GameObjects.h"
#include "OutputInterface.h"
#include <cmath>

class SDLOutput : public OutputInterface {
    private:
        WindowManager* wm;
        /*
         * description: Redraws one cell without affecting rest of board
         * return: void
         * precondition: A board and windowmanager exist, the cell is in bounds
         * postcondition: The cell is redrawn with the player colour
        */
        void drawCell(Cell c, Player p);
        /*
         * description: Uses plotter to draw a line from pos1 to pos2
         *              size is the line's thickness and color is its colour
         * return: void
         * precondition: Plotter is an active SDL_Plotter
         * postcondition: A new line is drawn on the plotter. 
         *                Doesn't update the screen.
        */
        void drawLine(SDL_Plotter& plotter, point pos1, point pos2, color color, int size);
        /*
         * description: Uses plotter to draw a hexagon with centrepoint pos
         *              borderColor and fillColor determine the colours of the
         *              outline and area of the hexagon respectively
         *              Radius is the hexagon's radius
         * return: void
         * precondition: Plotter is an active SDL_Plotter
         * postcondition: Hexagon is drawn on plotter.
         *                Doesn't update the screen.
        */
        void drawHexagon(SDL_Plotter& plotter, point pos, color boarderColor, color fillColor, int radius);
        /*
         * description: Fills an existing hexagon's area with color
         *              pos is hexagon's centre
         *              radius is the hex's radius
         * return: void
         * precondition: Plotter is an active SDL_Plotter
         *               A hexagon with centre at pos of radius radius exists
         * postcondition: Existing hexagon is edited to be filled with color
        */
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
