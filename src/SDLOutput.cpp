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

void SDLOutput::drawHexagon(point pos, color boarderColor, color fillColor, size_t radius) {
    for(int i = 0; i < 6; i++) {
        point pos1(pos.x + cos(i * PI / 3) * radius, pos.y + sin(i * PI / 3) * radius);
        point pos2(pos.x + cos((i+1) * PI / 3) * radius, pos.y + sin((i+1) * PI / 3) * radius);
        //makeBox(plotter, pos1, color, 5, 3);
        drawLine(pos1, pos2, boarderColor, 2);
    }
    //fill in hexagon logic:
    fillHexagon(fillColor, pos, radius);

}

void SDLOutput::fillHexagon(color fillColor, point pos, size_t radius) {
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

void SDLOutput::drawCell(Cell c, Player p){
    //IMPLEMENT ME
    return;
}

SDLOutput::SDLOutput (WindowManager* wm){
    //IMPLEMENT ME
}

SDLOutput::~SDLOutput(){
    //IMPLEMENT ME
}

void SDLOutput::output(GameLogic gl, Move lastValidMove){
   
    size_t radius = wm->CELL_RADIUS;
    for (size_t r = 0; r < gl.getBoardSize(); ++r) {
        for (size_t c = 0; c < gl.getBoardSize(); ++c) {
            int posX = round(((3.0/4) * radius) * (c - r)); 
            int posY = round((sqrt(3) * radius) * ((gl.getBoardSize() - 1.0 - r - c) / 4));
            point pos(posX, posY);
           int owner = gl.getCellOwner(r, c);
           color cellCol;
            if (owner == 0) {
                cellCol = wm->NOPLAYER_COLOR; //neutral 
            }
            else if (owner == 1) {
                cellCol = wm->PLAYER1_COLOR;
            }
            else {
                cellCol = wm->PLAYER2_COLOR;
            }

          drawHexagon(pos, wm->BORDER_COLOR, cellCol, radius);  
        }
    }

}
