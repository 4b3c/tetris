#ifndef SHAPES_H
#define SHAPES_H

#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}

const int shapeCells[7][4][4] = {
    { // O
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    { // S
        {0, 0, 0, 0},
        {0, 0, 2, 2},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    { // Z
        {0, 0, 0, 0},
        {0, 3, 3, 0},
        {0, 0, 3, 3},
        {0, 0, 0, 0}
    },
    { // I
        {0, 0, 4, 0},
        {0, 0, 4, 0},
        {0, 0, 4, 0},
        {0, 0, 4, 0}
    },
    { // J
        {0, 0, 0, 0},
        {0, 5, 5, 5},
        {0, 0, 0, 5},
        {0, 0, 0, 0}
    },
    { // L
        {0, 0, 0, 0},
        {0, 6, 6, 6},
        {0, 6, 0, 0},
        {0, 0, 0, 0}
    },
    { // T
        {7, 7, 7, 7},
        {7, 0, 0, 7},
        {7, 0, 0, 7},
        {7, 7, 7, 7}
    }
};


// Corresponding colors
const Color shapeColors[7] = {
	Color {230, 190,   0, 255}, // O
	Color { 10, 180,  60, 255}, // S
	Color {210,   0,   0, 255}, // Z
	Color {  0, 180, 200, 255}, // I
	Color {180, 110,   0, 255}, // J
	Color {  0,  90, 190, 255}, // L
	Color {170,   0, 200, 255}  // T
};

// Declare the Shape class
class Shape {
public:
    // Public member variables
    int shapeType;
    Color color;
    int** cells;

    // Constructor/Destructor
    Shape(int type);
    ~Shape();

    void draw(int, int, Texture2D* textures);

};

bool locationOpen(int**, int** cells, int, int);
bool addToGrid(int**, Shape*, int, int);
int** rotate(int**);

#endif
