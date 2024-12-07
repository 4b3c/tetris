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

void Shape::draw(int x, int y, Texture2D* textures) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (cells[row][col] != 0) {
                drawCell(x + col, y + row, textures[cells[row][col] - 1]);
            }
        }
    }
};

bool locationOpen(int** grid, int** cells, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (cells[row][col] != 0) {
                if (x + col < 0 || x + col > 9 || y + row > 19) {
                    return false;
                }
                if (grid[y + row][x + col] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
};

bool addToGrid(int** grid, Shape* shape, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (shape->cells[col][row] != 0) {
                grid[y + col][x + row] = shape->cells[col][row];
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