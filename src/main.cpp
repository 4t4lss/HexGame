/**
 * @file SDL_Plotter_Demo.cpp
 * @brief Demonstrates the complete public interface of SDL_Plotter version 4.0.
 *
 * @author Dr. William A. Booth
 * @version 1.0
 * @date 2026-08-29
 *
 * @details
 * This program is an interactive demonstration and test driver for
 * SDL_Plotter 4.0.  It exercises the plotting, display, keyboard, mouse,
 * timing, color-query, sound, and termination facilities exposed by the
 * SDL_Plotter class.
 *
 * The program demonstrates:
 *
 *   - Construction and destruction of an SDL_Plotter object
 *   - getRow() and getCol()
 *   - clear() and update()
 *   - All four plotPixel() overloads
 *   - Default black color arguments for plotPixel()
 *   - getColor()
 *   - getQuit() and setQuit()
 *   - kbhit() and getKey()
 *   - Arrow-key constants
 *   - mouseClick() and getMouseClick()
 *   - getMouseDown()
 *   - getMouseUp()
 *   - getMouseMotion()
 *   - getMouseLocation()
 *   - Sleep()
 *   - initSound(), playSound(), and quitSound()
 *
 * A sound file may be supplied as the first command-line argument.  If no
 * argument is supplied, the program attempts to use "sample.wav".
 *
 * Controls:
 *
 *   Arrow keys  Move the black cursor
 *   C           Clear the window
 *   R           Redraw the demonstration scene
 *   S           Play the initialized sound
 *   I           Initialize/reinitialize the sound
 *   X           Release the initialized sound
 *   M           Print the current mouse location
 *   U           Toggle direct mouse-up testing
 *   Q           Quit using SDL_Plotter::setQuit(true)
 *   Escape      Quit through SDL_Plotter::getQuit()
 *
 * Mouse behavior:
 *
 *   Mouse down       Draws a green marker
 *   Mouse movement   Draws a gray trail while events are available
 *   Mouse release    Normally enters SDL_Plotter's click queue and draws red
 *   U-mode release   Uses getMouseUp() directly and draws a blue marker
 */

#include "SDL_Plotter.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// -----------------------------------------------------------------------------
// Program constants
// -----------------------------------------------------------------------------

/** Height of the demonstration window in pixels. */
const int WINDOW_ROWS = 600;

/** Width of the demonstration window in pixels. */
const int WINDOW_COLS = 800;

/** Width and height of each color demonstration block. */
const int BLOCK_SIZE = 100;

/** Number of pixels moved by each arrow-key press. */
const int CURSOR_STEP = 10;

/** Delay between event-loop iterations, in milliseconds. */
const int LOOP_DELAY = 10;

/** Radius of mouse-event markers. */
const int MARKER_RADIUS = 5;

// -----------------------------------------------------------------------------
// Helper function prototypes
// -----------------------------------------------------------------------------

void drawRectangle(SDL_Plotter& plotter,
                   int left,
                   int top,
                   int width,
                   int height,
                   color c);

void drawMarker(SDL_Plotter& plotter,
                int centerX,
                int centerY,
                color c,
                int radius = MARKER_RADIUS);

void drawCursor(SDL_Plotter& plotter, point location);

void drawDemoScene(SDL_Plotter& plotter);

void printPixelValue(SDL_Plotter& plotter, int x, int y);

void printInstructions(const string& soundFile);

// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------

/**
 * @brief Runs the SDL_Plotter 4.0 demonstration.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line argument array. argv[1], when present, is the path
 *             to a sound file used by the sound demonstration.
 * @return 0 when the demonstration terminates normally; 1 if SDL_Plotter
 *         cannot be constructed.
 */
int main(int argc, char* argv[]) {
    const string soundFile = (argc > 1) ? argv[1] : "sample.wav";

    try {
        // -----------------------------------------------------------------
        // Construction, dimensions, clear(), update(), plotting, getColor()
        // -----------------------------------------------------------------
        SDL_Plotter plotter(WINDOW_ROWS, WINDOW_COLS, true);

        // Explicitly demonstrate setQuit(false).  The constructor already
        // begins in this state, but this call documents and tests the method.
        plotter.setQuit(false);

        cout << "SDL_Plotter 4.0 Demonstration" << endl;
        cout << "Window dimensions: "
             << plotter.getCol() << " columns x "
             << plotter.getRow() << " rows" << endl;

        printInstructions(soundFile);

        drawDemoScene(plotter);
        plotter.update();

        // Demonstrate getColor() by reading a known pixel from each block.
        cout << "\nPacked pixel values from the demonstration blocks:" << endl;
        printPixelValue(plotter, 75, 75);
        printPixelValue(plotter, 225, 75);
        printPixelValue(plotter, 375, 75);
        printPixelValue(plotter, 525, 75);

        // -----------------------------------------------------------------
        // Sound initialization
        // -----------------------------------------------------------------
        // initSound() fails gracefully if the file is missing or sound is not
        // available.  SDL_Plotter reports the detailed error through SDL.
        plotter.initSound(soundFile);

        // Cursor used to demonstrate queued keyboard input and arrow constants.
        point cursor(plotter.getCol() / 2, plotter.getRow() / 2);
        drawCursor(plotter, cursor);
        plotter.update();

        bool done = false;
        bool directMouseUpMode = false;

        // -----------------------------------------------------------------
        // Interactive event loop
        // -----------------------------------------------------------------
        while (!done) {
            bool imageChanged = false;
            int mouseX = 0;
            int mouseY = 0;

            // getMouseDown() inspects the next SDL event directly.
            if (plotter.getMouseDown(mouseX, mouseY)) {
                cout << "Mouse down: (" << mouseX << ", " << mouseY << ")"
                     << endl;
                drawMarker(plotter, mouseX, mouseY, color(0, 180, 0));
                imageChanged = true;
            }

            // getMouseMotion() also works directly with SDL's event queue.
            if (plotter.getMouseMotion(mouseX, mouseY)) {
                drawMarker(plotter, mouseX, mouseY, color(160, 160, 160), 1);
                imageChanged = true;
            }

            // The direct mouse-up method is placed in a separate mode because
            // consuming a mouse-up event here prevents getQuit() from placing
            // the same event in SDL_Plotter's queued-click interface.
            if (directMouseUpMode && plotter.getMouseUp(mouseX, mouseY)) {
                cout << "Direct mouse up: ("
                     << mouseX << ", " << mouseY << ")" << endl;
                drawMarker(plotter, mouseX, mouseY, color(0, 0, 255));
                imageChanged = true;
            }

            // getQuit() processes the remaining SDL events.  Among other work,
            // it places text/arrow input in the key queue and normal mouse-up
            // events in the click queue.
            done = plotter.getQuit();

            // -------------------------------------------------------------
            // Queued keyboard input: kbhit() and getKey()
            // -------------------------------------------------------------
            while (plotter.kbhit()) {
                const char key = plotter.getKey();

                if (key == UP_ARROW) {
                    cursor.y -= CURSOR_STEP;
                    cout << "UP_ARROW" << endl;
                } else if (key == DOWN_ARROW) {
                    cursor.y += CURSOR_STEP;
                    cout << "DOWN_ARROW" << endl;
                } else if (key == LEFT_ARROW) {
                    cursor.x -= CURSOR_STEP;
                    cout << "LEFT_ARROW" << endl;
                } else if (key == RIGHT_ARROW) {
                    cursor.x += CURSOR_STEP;
                    cout << "RIGHT_ARROW" << endl;
                } else if (key == 'c' || key == 'C') {
                    // Demonstrate clear().  The change becomes visible only
                    // after update() is called later in this loop iteration.
                    plotter.clear();
                    cout << "Window cleared." << endl;
                } else if (key == 'r' || key == 'R') {
                    drawDemoScene(plotter);
                    cout << "Demonstration scene redrawn." << endl;
                } else if (key == 's' || key == 'S') {
                    plotter.playSound(soundFile);
                    cout << "playSound(\"" << soundFile << "\")" << endl;
                } else if (key == 'i' || key == 'I') {
                    plotter.initSound(soundFile);
                    cout << "initSound(\"" << soundFile << "\")" << endl;
                } else if (key == 'x' || key == 'X') {
                    plotter.quitSound(soundFile);
                    cout << "quitSound(\"" << soundFile << "\")" << endl;
                } else if (key == 'm' || key == 'M') {
                    // getMouseLocation() also prints the coordinates because
                    // that behavior is retained by SDL_Plotter 4.0.
                    plotter.getMouseLocation(mouseX, mouseY);
                    cout << "Current mouse location returned as: ("
                         << mouseX << ", " << mouseY << ")" << endl;
                } else if (key == 'u' || key == 'U') {
                    directMouseUpMode = !directMouseUpMode;
                    cout << "Direct getMouseUp() mode: "
                         << (directMouseUpMode ? "ON" : "OFF") << endl;
                } else if (key == 'q' || key == 'Q') {
                    // Demonstrate explicit program-controlled termination.
                    plotter.setQuit(true);
                    done = true;
                } else if (key != '\0') {
                    cout << "Keyboard character: '" << key << "'" << endl;
                }

                // Keep the cursor inside the plotting area.
                if (cursor.x < 0) {
                    cursor.x = 0;
                }
                if (cursor.x >= plotter.getCol()) {
                    cursor.x = plotter.getCol() - 1;
                }
                if (cursor.y < 0) {
                    cursor.y = 0;
                }
                if (cursor.y >= plotter.getRow()) {
                    cursor.y = plotter.getRow() - 1;
                }

                drawCursor(plotter, cursor);
                imageChanged = true;
            }

            // -------------------------------------------------------------
            // Queued mouse input: mouseClick() and getMouseClick()
            // -------------------------------------------------------------
            while (plotter.mouseClick()) {
                const point click = plotter.getMouseClick();

                cout << "Queued mouse click: ("
                     << click.x << ", " << click.y << ")" << endl;

                drawMarker(plotter,
                           click.x,
                           click.y,
                           color(220, 0, 0));
                imageChanged = true;
            }

            // update() is required to make changes to the pixel buffer visible.
            if (imageChanged) {
                plotter.update();
            }

            // Demonstrate SDL_Plotter's millisecond delay function and avoid a
            // busy event loop that would consume an entire CPU core.
            plotter.Sleep(LOOP_DELAY);
        }

        // Release the loaded sound explicitly.  The SDL_Plotter destructor will
        // also release any sound that remains initialized.
        plotter.quitSound(soundFile);

        cout << "SDL_Plotter demonstration complete." << endl;
    } catch (const exception& e) {
        cerr << "Unable to run SDL_Plotter demonstration: "
             << e.what() << endl;
        return 1;
    }

    return 0;
}

// -----------------------------------------------------------------------------
// Helper function definitions
// -----------------------------------------------------------------------------

/**
 * @brief Draws a filled rectangle using SDL_Plotter pixels.
 *
 * @param plotter SDL_Plotter object receiving the pixels.
 * @param left X coordinate of the rectangle's left edge.
 * @param top Y coordinate of the rectangle's top edge.
 * @param width Rectangle width in pixels.
 * @param height Rectangle height in pixels.
 * @param c Fill color.
 */
void drawRectangle(SDL_Plotter& plotter,
                   int left,
                   int top,
                   int width,
                   int height,
                   color c) {
    for (int y = top; y < top + height; ++y) {
        for (int x = left; x < left + width; ++x) {
            plotter.plotPixel(x, y, c);
        }
    }
}

/**
 * @brief Draws a small filled square centered at a location.
 *
 * @param plotter SDL_Plotter object receiving the pixels.
 * @param centerX Center x coordinate.
 * @param centerY Center y coordinate.
 * @param c Marker color.
 * @param radius Number of pixels drawn outward from the center.
 */
void drawMarker(SDL_Plotter& plotter,
                int centerX,
                int centerY,
                color c,
                int radius) {
    for (int y = centerY - radius; y <= centerY + radius; ++y) {
        for (int x = centerX - radius; x <= centerX + radius; ++x) {
            plotter.plotPixel(point(x, y), c);
        }
    }
}

/**
 * @brief Draws a black cross marking the current keyboard-controlled cursor.
 *
 * @param plotter SDL_Plotter object receiving the pixels.
 * @param location Cursor center.
 *
 * @details
 * Calls plotPixel() without an explicit color to demonstrate SDL_Plotter's
 * default black color argument.
 */
void drawCursor(SDL_Plotter& plotter, point location) {
    const int radius = 6;

    for (int offset = -radius; offset <= radius; ++offset) {
        // Demonstrate the default-color integer-coordinate overload.
        plotter.plotPixel(location.x + offset, location.y);

        // Demonstrate the default-color point overload.
        plotter.plotPixel(point(location.x, location.y + offset));
    }
}

/**
 * @brief Draws a scene that explicitly exercises every plotPixel() overload.
 *
 * @param plotter SDL_Plotter object receiving the scene.
 *
 * @details
 * Four colored blocks across the top of the window are drawn using four
 * distinct public plotPixel() forms:
 *
 *   1. plotPixel(x, y, r, g, b)
 *   2. plotPixel(point, r, g, b)
 *   3. plotPixel(x, y, color)
 *   4. plotPixel(point, color)
 *
 * A diagonal RGB gradient is also drawn to illustrate per-pixel graphics.
 */
void drawDemoScene(SDL_Plotter& plotter) {
    plotter.clear();

    // Block 1: plotPixel(int x, int y, int r, int g, int b)
    for (int y = 25; y < 25 + BLOCK_SIZE; ++y) {
        for (int x = 25; x < 25 + BLOCK_SIZE; ++x) {
            plotter.plotPixel(x, y, 255, 0, 0);
        }
    }

    // Block 2: plotPixel(point p, int r, int g, int b)
    for (int y = 25; y < 25 + BLOCK_SIZE; ++y) {
        for (int x = 175; x < 175 + BLOCK_SIZE; ++x) {
            plotter.plotPixel(point(x, y), 0, 255, 0);
        }
    }

    // Block 3: plotPixel(int x, int y, color c)
    for (int y = 25; y < 25 + BLOCK_SIZE; ++y) {
        for (int x = 325; x < 325 + BLOCK_SIZE; ++x) {
            plotter.plotPixel(x, y, color(0, 0, 255));
        }
    }

    // Block 4: plotPixel(point p, color c)
    for (int y = 25; y < 25 + BLOCK_SIZE; ++y) {
        for (int x = 475; x < 475 + BLOCK_SIZE; ++x) {
            plotter.plotPixel(point(x, y), color(255, 0, 255));
        }
    }

    // Draw a color gradient across the lower portion of the window.  This
    // illustrates the intended pixel-oriented nature of SDL_Plotter.
    const int gradientTop = 180;
    const int gradientBottom = plotter.getRow() - 60;

    for (int y = gradientTop; y < gradientBottom; ++y) {
        for (int x = 40; x < plotter.getCol() - 40; ++x) {
            const int r = (255 * x) / plotter.getCol();
            const int g = (255 * (y - gradientTop)) /
                          (gradientBottom - gradientTop);
            const int b = 255 - r;

            plotter.plotPixel(x, y, r, g, b);
        }
    }

    // Use the general rectangle helper to add a black baseline near the
    // bottom of the scene.
    drawRectangle(plotter,
                  40,
                  plotter.getRow() - 40,
                  plotter.getCol() - 80,
                  5,
                  color(0, 0, 0));
}

/**
 * @brief Prints the packed color value stored at a pixel coordinate.
 *
 * @param plotter SDL_Plotter whose pixel buffer is queried.
 * @param x Pixel x coordinate.
 * @param y Pixel y coordinate.
 */
void printPixelValue(SDL_Plotter& plotter, int x, int y) {
    const Uint32 value = plotter.getColor(x, y);

    cout << "  (" << setw(3) << x << ", " << setw(3) << y << ") = 0x"
         << hex << uppercase << setw(8) << setfill('0') << value
         << dec << nouppercase << setfill(' ') << endl;
}

/**
 * @brief Prints the interactive controls used by the demonstration.
 *
 * @param soundFile Sound file selected for the sound demonstration.
 */
void printInstructions(const string& soundFile) {
    cout << "\nSound file: " << soundFile << endl;
    cout << "\nControls" << endl;
    cout << "--------" << endl;
    cout << "Arrow keys : move the black cursor" << endl;
    cout << "C          : clear the window" << endl;
    cout << "R          : redraw the demonstration scene" << endl;
    cout << "S          : play the initialized sound" << endl;
    cout << "I          : initialize/reinitialize the sound" << endl;
    cout << "X          : release the initialized sound" << endl;
    cout << "M          : display current mouse location" << endl;
    cout << "U          : toggle direct getMouseUp() mode" << endl;
    cout << "Q          : quit using setQuit(true)" << endl;
    cout << "Escape     : quit using getQuit()" << endl;
    cout << "\nMouse" << endl;
    cout << "-----" << endl;
    cout << "Down       : green marker via getMouseDown()" << endl;
    cout << "Move       : gray trail via getMouseMotion()" << endl;
    cout << "Release    : red marker via mouseClick()/getMouseClick()" << endl;
    cout << "U-mode up  : blue marker via getMouseUp()" << endl;
}
