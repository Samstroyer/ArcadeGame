#include "raylib.h"

typedef struct
{
    int x;
    int y;
    int damage;
    float speed;
} Player;

Texture2D player_texture;
Texture2D enemy_texture;

void LoadImages()
{
    Image player_image = LoadImage("Sprites/player.png");
    Image enemy_image = LoadImage("Sprites/player.png");

    ImageResize(&player_image, 25, 25);
    ImageResize(&enemy_image, 25, 25);

    player_texture = LoadTextureFromImage(player_image);
    enemy_texture = LoadTextureFromImage(enemy_image);

    UnloadImage(player_image);
    UnloadImage(enemy_image);
}

int main()
{
    SetTargetFPS(10);
    InitWindow(800, 800, "Galaga 2.0");
    LoadImages();
    Player p;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(player_texture, 25, 25, WHITE);
        EndDrawing();
    }

    return 0;
}