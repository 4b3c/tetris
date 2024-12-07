#include <iostream>
#include "utils.h"
#include "shapes.h"

#define CLITERAL(type) type
extern "C" {
    #include "raylib.h"
}




int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(cellSize * 32, cellSize * 22, "Tetris");

    Shape Z(2);
    Z.posX = 7;
    Z.posY = 3;


    while (!WindowShouldClose()) {
        BeginDrawing();
        drawGrid();
        Z.draw();


        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
