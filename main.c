#include "raylib.h"

int main()
{
    SetTargetFPS(10);
    InitWindow(100, 100, "test");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawRectangle(25, 25, 50, 50, RED);
        EndDrawing();
    }
    return 0;
}