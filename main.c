#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include "structs.c"
#include "enemy.c"
#include "player.c"

// Load and resize the player and enemy images to textures
void LoadImages()
{
    Image player_image = LoadImage("Sprites/player.png");
    Image enemy_image = LoadImage("Sprites/enemy.png");

    ImageResize(&player_image, 25, 25);
    ImageResize(&enemy_image, 25, 25);

    ImageRotateCCW(&enemy_image);
    ImageRotateCCW(&enemy_image);

    player_texture = LoadTextureFromImage(player_image);
    enemy_texture = LoadTextureFromImage(enemy_image);

    UnloadImage(player_image);
    UnloadImage(enemy_image);
}

// Main function
int main()
{
    // All Initializations
    SetTargetFPS(60);
    InitWindow(800, 800, "Galaga 2.0");
    LoadImages();

    Enemy enemies[200];

    Player p;
    p.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
    p.y = GetScreenHeight() - 40;
    p.damage = 1;
    p.speed = 2.5f;

    Setup(enemies, &p);

    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Input(&p);
        CheckEnemies(enemies);

        UpdateProjectiles(&p);
        MoveEnemies(enemies, &p);

        CheckProjectileCollisions(enemies, &p);

        RenderPlayer(&p);
        RenderEnemies(enemies);

        // printf("Score: %li\n", p.points);

        EndDrawing();
    }

    return 0;
}