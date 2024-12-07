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

void shuffle(int* arr, int size) {
    for (int i = 0; i < size*3; i++) {
        int index1 = rand() % size;
        int index2 = rand() % size;

        int temp = arr[index2];
        arr[index2] = arr[index1];
        arr[index1] = temp;
    }
}


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(cellSize * 32, cellSize * 22, "Tetris");

    double timer = GetTime();
    int hat[7] = {0, 1, 2, 3, 4, 5, 6};
    shuffle(hat, 7);
    int counter = 0;

    srand(timer);
    rand(); // Seems like this helps
    Shape* focus = new Shape(hat[counter++]);
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
        if (GetTime() > (timer + 0.2)) {
            timer = GetTime();
            if (locationOpen(grid, focus->cells, x, y + 1)) {
                y++;
            } else {
                addToGrid(grid, focus, x, y);
                checkGrid(grid);
                delete focus;
                if (counter == 7) { shuffle(hat, 7); counter = 0;}
                focus = new Shape(hat[counter++]);
                x = 3;
                y = 0;
            }
        }

        EndDrawing();

    }

    CloseWindow();

    // deallocates grid memory
    for (int row = 0; row < 20; row++) {
        delete[] grid[row];
    }
    delete[] grid;
    delete focus;

    return 0;
}
