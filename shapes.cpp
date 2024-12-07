#include <iostream>
#include "shapes.h"
#include "utils.h"
#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}

using namespace std;


Shape::Shape(int type) {
    cout << "Creating shape of type: " << type << endl;
    shapeType = type;
    color = shapeColors[shapeType];

    // Copy the selected shape into the cells array
    cells = new int*[4];
    for (int row = 0; row < 4; row++) {
        cells[row] = new int[4];
        for (int col = 0; col < 4; col++) {
            cells[row][col] = shapeCells[shapeType][row][col];
        }
    }
}

Shape::~Shape() {
    if (cells == nullptr) { return; }
    for (int row = 0; row < 4; row++) {
        delete[] cells[row];
    }
    delete[] cells;
}

void Shape::draw(int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (cells[row][col] == 1) {
                drawCell(x + col, y + row, color);
            }
        }
    }
};

bool locationOpen(Color** grid, int** cells, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (cells[row][col] == 1) {
                if (x + col < 0 || x + col > 9 || y + row > 19) {
                    cout << "Not open 2: " << x << ", " << y << endl;
                    return false;
                }
                if (!ColorIsEqual(grid[y + row][x + col], Color {0, 0, 0, 255})) {
                    cout << "Not open 1: " << grid[y + row][x + col].r << endl;
                    return false;
                }
            }
        }
    }
    return true;
};

bool addToGrid(Color** grid, Shape* shape, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (shape->cells[col][row] == 1) {
                grid[y + col][x + row] = shape->color;
            }
        }
    }
    return true;
};

int** rotate(int** cells) {
    // Allocate memory for the new 4x4 matrix
    int** newCells = new int*[4];
    for (int i = 0; i < 4; i++) {
        newCells[i] = new int[4];
    }

    // Rotate the matrix to the right (clockwise)
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            newCells[col][3 - row] = cells[row][col];
        }
    }

    return newCells;
}