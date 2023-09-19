#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include "textures.c"
#include "structs.c"
#include "formations.c"
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
    projectile_texture = LoadTexture("Sprites/projectile.png");

    UnloadImage(player_image);
    UnloadImage(enemy_image);
}

// Setup all the members of the arrays
void Setup(Enemy *enemies, Player *p)
{
    p->points = 0;

    for (int i = 0; i < 200; i++)
    {
        enemies[i].exist = false;
        enemies[i].target_timer = 0;
    }
    for (int i = 0; i < 20; i++)
    {
        p->projectiles[i].exist = false;
    }
    for (int i = 0; i < 50; i++)
    {
        enemy_projectiles[i].exist = false;
    }
    for (int i = 0; i < 4; i++)
    {
        formations[i].exist = false;
    }
}

// Main function
int main()
{
    // All Initializations
    InitWindow(800, 800, "Galaga 2.0");
    SetTargetFPS(100);
    LoadImages();

    Enemy enemies[200];

    Player p;
    p.pos.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
    p.pos.y = GetScreenHeight() - 40;
    p.selected_projectile = PROJECTILE_SLOW; // 0
    p.speed = 2.5f;

    Setup(enemies, &p);

    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        // DrawTexture(background, -150, 0, WHITE);

        Input(&p);
        CheckEnemies(enemies);
        FireEnemies(enemies);

        UpdateProjectiles(&p);
        MoveEnemies(enemies, &p);
        UpdateFormations();

        CheckProjectileCollisions(enemies, &p);
        CheckFormationMembersHit(&p);

        RenderPlayer(&p);
        RenderEnemies(enemies);
        RenderEnemyProjectiles(enemies);
        RenderFormations();

        DrawText(TextFormat("Points: %i", p.points), 20, 750, 45, WHITE);

        EndDrawing();
    }
    return 0;
}