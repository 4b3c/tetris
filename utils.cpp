#include <iostream>
#include "utils.h"
#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}

using namespace std;


int gridToPixelX(int x) { return gridX + (x * cellSize); }
int gridToPixelY(int y) { return gridY + (y * cellSize); }

void drawGrid(int** grid, Texture2D* textures) {
    for (int col = 0; col < 11; col++) {
        DrawLine(gridToPixelX(col), gridToPixelY(0), gridToPixelX(col), gridToPixelY(20), WHITE);
        DrawLine(gridToPixelX(col) + 1, gridToPixelY(0), gridToPixelX(col) + 1, gridToPixelY(20), BLACK);
    }
    for (int row = 0; row < 21; row++) {
        DrawLine(gridToPixelX(0), gridToPixelY(row), gridToPixelX(10), gridToPixelY(row), WHITE);
        DrawLine(gridToPixelX(0), gridToPixelY(row) + 1, gridToPixelX(10), gridToPixelY(row) + 1, BLACK);
    }
    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 10; col++) {
            drawCell(col, row, textures[grid[row][col] - 1]);
        }
    }
}

bool drawCell(int x, int y, Texture2D texture) {
    if (x < 0 || x > 9 || y < 0 || y > 19) { return false; }
    Vector2 position = (Vector2){(float)gridToPixelX(x), (float)gridToPixelY(y)};
    DrawTextureEx(texture, position, 0, 4.0, WHITE);
    return true;
}

bool checkRow(int** grid, int row) {
    for (int col = 0; col < 10; col++) {
        if (grid[row][col] == 0) {
            return false;
        }
    }
    return true;
}

int checkGrid(int** grid) {
    int cleared = 0;
    for (int row = 19; row >= 0; row--) {
        if (checkRow(grid, row)) {
            cleared += 1;
            delete[] grid[row];
            for (int row2 = row; row > 0; row--) {
                grid[row] = grid[row - 1];
            }
            grid[0] = new int[10];
            for (int col = 0; col < 10; col++) {
                grid[row][col] = 0;
            }
            cleared += checkGrid(grid);
            row++;
        }
    }
    return cleared;
}