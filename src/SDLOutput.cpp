#include "SDLOutput.h"

void drawLine(SDL_Plotter& plotter, point pos1, point pos2, color color, int size) {
    int dx = abs(pos2.x - pos1.x);
    int dy = abs(pos2.y - pos1.y);
    int sx, sy;
    int err = dx - dy;
    int sizeOffset = size/2;

    if (pos1.x < pos2.x) {
        sx = 1;
    }
    else {
        sx = -1;
    }

    if (pos1.y < pos2.y) {
        sy = 1;
    }
    else {
        sy = -1;
    }

    while (pos1.x != pos2.x + sx || pos1.y != pos2.y + sy) {

        for (int sizeY = -sizeOffset; sizeY <= sizeOffset; ++sizeY) {
            for (int sizeX = -sizeOffset; sizeX <= sizeOffset; ++sizeX) {
                plotter.plotPixel(pos1.x + sizeX, pos1.y + sizeY, color.R, color.G, color.B);
            }
        }
        if (pos1.x == pos2.x && pos1.y == pos2.y) {
            pos1.x += sx;
            pos1.y += sy;
        }
        else {
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                pos1.x += sx;
            }
            if (e2 < dx) {
                err += dx;
                pos1.y += sy;
            }
        }
    };

}

void drawHexagon(SDL_Plotter& plotter, point pos, color color, color fillColor, int radius) {
    for(int i = 0; i < 6; i++) {
        point pos1(pos.x + cos(i * PI / 3) * radius, pos.y + sin(i * PI / 3) * radius);
        point pos2(pos.x + cos((i+1) * PI / 3) * radius, pos.y + sin((i+1) * PI / 3) * radius);
        //makeBox(plotter, pos1, color, 5, 3);
        drawLine(plotter, pos1, pos2, color, 2);
    }
    //fill in hexagon logic:
    fillHexagon(plotter, fillColor, pos, radius);

}

void fillHexagon(SDL_Plotter& plotter, color color, point pos, int radius) {
    for (int y = -radius; y < radius; ++y) {
        for (int x = -radius; x < radius; ++x) {
            if (abs(y) <= -1 * sqrt(3) * (abs(x) - radius) &&
                    abs(y) <= radius * sqrt(3) / 2) {
                size_t colorCheck = plotter.getColor(x + pos.x, y + pos.y);
                if (colorCheck != 0) {
                    plotter.plotPixel(x + pos.x, y + pos.y, color.R, color.G, color.B);
                }
            }
        }
    }
}

void drawCell(Cell c, Player p){
    //IMPLEMENT ME
    return;
}

SDLOutput (WindowManager* wm){
    //IMPLEMENT ME
}

~SDLOutput(){
    //IMPLEMENT ME
}

void output(GameLogic gl, Move lastValidMove){
    //IMPLEMENT ME
}
