#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "shapes.h"

#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}

using namespace std;


void print(int** cells) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            cout << cells[row][col] << ", ";
        }
        cout << endl;
    }
}


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(cellSize * 32, cellSize * 22, "Tetris");

    double counter = GetTime();

    srand(counter);
    rand(); // Seems like this helps
    Shape* focus = new Shape(rand() % 7);
    int x = 3;
    int y = 0;

    // creates a 2d array of colors for our grid to store old shapes
    Color** grid = new Color*[20];
    for (int row = 0; row < 20; row++) {
        grid[row] = new Color[10];
        for (int col = 0; col < 10; col++) {
            grid[row][col] = Color {0, 0, 0, 255};
        }
    }


    while (!WindowShouldClose()) {
        // draws things to the screen
        BeginDrawing();

        ClearBackground(GRAY);
        drawGrid(grid);
        focus->draw(x, y);

        if (IsKeyPressed(KEY_RIGHT)) {
            if (locationOpen(grid, focus->cells, x + 1, y)) {
                x++;
            }
        } else if (IsKeyPressed(KEY_LEFT)) {
            if (locationOpen(grid, focus->cells, x - 1, y)) {
                x--;
            }
        } else if (IsKeyPressed(KEY_UP)) {
            int** rotated = rotate(focus->cells);
            if (locationOpen(grid, rotated, x, y)) {
                for (int row = 0; row < 4; row++) {
                    delete[] focus->cells[row];
                }
                delete focus->cells;
                focus->cells = rotated;
            } else {
                for (int row = 0; row < 4; row++) {
                    delete[] rotated[row];
                }
                delete[] rotated;
            }
        }

        // incrememnets the game state every 0.6 seconds
        if (GetTime() > (counter + 0.3)) {
            counter = GetTime();
            if (locationOpen(grid, focus->cells, x, y + 1)) {
                y++;
            } else {
                addToGrid(grid, focus, x, y);
                delete focus;
                focus = new Shape(rand() % 7);
                x = 3;
                y = 0;
            }
        }

        EndDrawing();

    }

    CloseWindow();

    // deallocates memory for the grid
    for (int row = 0; row < 20; row++) {
        delete[] grid[row];
    }
    delete[] grid;
    delete focus;

    return 0;
}
