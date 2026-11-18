/*
 * Author: Sam D'Agostino
 * Assignment Title: SDL Output
 * Assignment Description: Generates the window and Displays the board using
 *  SDL plotter 
 * Due Date: 11/18/2026
 * Date Created: 11/18/2026
 * Date Last Modified: 11/18/2026
 */
#include "SDLOutput.h"

bool operator==(const color& lhs, const color& rhs) {
    return lhs.R == rhs.R &&
        lhs.G == rhs.G &&
        lhs.B == rhs.B; 
}

void SDLOutput::drawLine(point pos1, point pos2, color lineColor, int size) {
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
                wm->plotPixel(pos1.x + sizeX, pos1.y + sizeY, lineColor);
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

void SDLOutput::drawHexagon(const point& pos, const color& borderColor,
        const color& fillColor, const int& radius) {
    for(int i = 0; i < 6; i++) {
        point pos1(pos.x + cos(i * PI / 3) * radius,
                pos.y + sin(i * PI / 3) * radius);
        point pos2(pos.x + cos((i+1) * PI / 3) * radius,
                pos.y + sin((i+1) * PI / 3) * radius);
        drawLine(pos1, pos2, borderColor, 2);
    }
    fillHexagon(fillColor, pos, radius);

}

void SDLOutput::fillHexagon(color fillColor, point pos, int radius) {
    for (int y = -radius; y < radius; ++y) {
        for (int x = -radius; x < radius; ++x) {
            if (abs(y) <= -1 * sqrt(3) * (abs(x) - radius) &&
                    abs(y) <= radius * sqrt(3) / 2) {
                size_t colorCheck = wm->getColor(x + pos.x, y + pos.y);
                if (colorCheck != 0) {
                    wm->plotPixel(x + pos.x, y + pos.y, fillColor);
                }
            }
        }
    }
}

void SDLOutput::drawCell(int row, int col, int p) {
        int posX = -round(3.0 * wm->CELL_RADIUS* (col - row) / 2); 
        int posY = -round((SQRT_3 * wm->CELL_RADIUS) *
                (wm->BOARD_SIZE - 1.0 - row - col) / 2);
        point pos(posX + wm->CENTERX, posY + wm->CENTERY);
        color cellCol;
        if (p == 0) {
            cellCol = wm->NOPLAYER_COLOR; //neutral 
        }
        else if (p == 1) {
            cellCol = wm->PLAYER1_COLOR;
        }
        else {
            cellCol = wm->PLAYER2_COLOR;
        }

        drawHexagon(pos, wm->BORDER_COLOR, cellCol, wm->CELL_RADIUS);  
}

SDLOutput::SDLOutput (WindowManager* wm) : wm{wm}{
    //IMPLEMENT ME
}

SDLOutput::~SDLOutput(){
    //IMPLEMENT ME
}

void SDLOutput::output(GameLogic gl, Move lastValidMove){

    int radius = wm->CELL_RADIUS;
    int size = gl.getBoardSize();
    for (int c = 0; c < size; ++c) {
        for (int r = 0; r < size; ++r) {
            Cell h(r,c);
            int p = gl.getCellOwner(r,c);
            drawCell(r,c,p);
        }
    }
    wm->update();

}
