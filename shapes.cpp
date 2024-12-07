#include "shapes.h"
#include "utils.h"
#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}



Shape::Shape(int type) {
    posX = 0;
    posY = 0;
    shapeType = type;
    color = shapeColors[shapeType];

    // Copy the selected shape into the cells array
    for (int row = 0; row < 4; row++) {
        for (int j = 0; j < 4; j++) {
            cells[row][j] = shapeCells[shapeType][row][j];
        }
    }

}

void Shape::draw() {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (cells[row][col] == 1) {
                drawCell(row, col, color);
            }
        }
    }

};