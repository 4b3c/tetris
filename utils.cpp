#include "utils.h"
#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}


int gridToPixelX(int x) { return gridX + (x * cellSize); }
int gridToPixelY(int y) { return gridY + (y * cellSize); }

void initGrid(Color** grid) {
    for (int row = 0; row < 21; row++) {
        for (int col = 0; col < 11; col++) {
            grid[row][col] = Color {0, 0, 0, 255};
        }
    }
}

void drawGrid(Color** grid) {
    for (int col = 0; col < 11; col++) {
        DrawLine(gridToPixelX(col), gridToPixelY(0), gridToPixelX(col), gridToPixelY(20), WHITE);
    }
    for (int row = 0; row < 21; row++) {
        DrawLine(gridToPixelX(0), gridToPixelY(row), gridToPixelX(10), gridToPixelY(row), WHITE);
    }
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 10; col++) {
            drawCell(col, row, grid[row][col]);
        }
    }
}

bool drawCell(int x, int y, Color color) {
    if (x < 0 || x > 9 || y < 0 || y > 19) { return false; }
    DrawRectangle(gridToPixelX(x), gridToPixelY(y), cellSize - 1, cellSize - 1, color);
    return true;
}
