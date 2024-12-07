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
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            cells[row][col] = shapeCells[shapeType][row][col];
        }
    }

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

bool locationOpen(Color** grid, Shape shape, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (shape.cells[row][col] == 1) {
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

bool addToGrid(Color** grid, Shape shape, int x, int y) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (shape.cells[col][row] == 1) {
                grid[y + col][x + row] = shape.color;
            }
        }
    }
    return true;
};