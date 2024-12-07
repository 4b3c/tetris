#ifndef UTILS_H
#define UTILS_H

#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}

const int gridX = 32;
const int gridY = 32;
const int cellSize = 32;

int gridToPixelX(int);
int gridToPixelY(int);

void drawGrid();
void drawCell(int, int, Color);


#endif