#include "utils.h"
#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}


int gridToPixelX(int x) { return gridX + (x * cellSize); }
int gridToPixelY(int y) { return gridY + (y * cellSize); }

void drawGrid() {
    for (int col = 0; col < 11; col++) {
        DrawLine(gridToPixelX(col), gridToPixelY(0), gridToPixelX(col), gridToPixelY(20), WHITE);
    }
    for (int row = 0; row < 21; row++) {
        DrawLine(gridToPixelX(0), gridToPixelY(row), gridToPixelX(10), gridToPixelY(row), WHITE);
    }
}

void drawCell(int x, int y, Color color) {
    DrawRectangle(gridToPixelX(x), gridToPixelY(y), cellSize - 1, cellSize - 1, color);
}
