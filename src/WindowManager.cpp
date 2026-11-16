#include "WindowManager.h"

WindowManager::WindowManager(size_t boardSize): {
    g(HEIGHT, WIDTH, false);
    newSize(boardSize);
}

WindowManager::~WindowManager() {
    delete g;
}

void WindowManager::newSize(size_t boardSize) {
    CELL_RADIUS = static_cast<int>(BOARD_SIZE_SCALE * 2.0 * WIDTH / boardSize / SQRT_3);
}
