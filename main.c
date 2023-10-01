#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdio.h>
#include "textures.c"
#include "structs.c"
#include "explosion.c"
#include "formations.c"
#include "enemy.c"
#include "player.c"
#include "menu.c"

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
    explosion_texture = LoadTexture("Sprites/explosion_sheet.png");
    title_texture = LoadTexture("Sprites/title.png");

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
    for (int i = 0; i < max_formations; i++)
    {
        formations[i].exist = false;
    }
    for (int i = 0; i < max_formation_projectiles; i++)
    {
        formation_projectiles[i].exist = false;
    }
}

// Main function
int main()
{
    // All Initializations
    InitWindow(800, 800, "Galaga 2.0");
    SetTargetFPS(100);
    LoadImages();

    while (!WindowShouldClose())
    {
        switch (current_menu)
        {
        case START_MENU:
        {
            RenderMenu();
            break;
        }
        case GAME_MENU:
        {
            Enemy enemies[200];

            Player p;
            p.pos.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
            p.pos.y = GetScreenHeight() - 40;
            p.selected_projectile = PROJECTILE_SLOW; // 0
            p.speed = 2.5f;
            p.hp = 3;

            Setup(enemies, &p);

            StartAnimation();

            // Game loop
            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);

                Rain();

                Input(&p);
                CheckEnemies(enemies);
                FireEnemies(enemies);

                UpdateProjectiles(&p);
                MoveEnemies(enemies, &p);
                UpdateFormations();
                FormationsShoot();
                UpdateAndDrawFormationProjectiles();

                CheckProjectileCollisions(enemies, &p);
                CheckFormationMembersHit(&p);
                CheckPlayerHit(&p);

                RenderPlayerAndHP(&p);
                RenderEnemies(enemies);
                RenderExplosions();
                RenderEnemyProjectiles(enemies);
                RenderFormations();

                DrawText(TextFormat("Points: %i", p.points), 20, 750, 45, WHITE);

                EndDrawing();

                if (p.hp > 0)
                    continue;

                break;
            }

            short timer = 180;
            while (timer > 0 && !WindowShouldClose())
            {
                int sprite_number = Remap(timer, 180, 0, 0, 3);

                BeginDrawing();
                ClearBackground(BLACK);

                DrawTexturePro(explosion_texture,
                               (Rectangle){sprite_number * 10, 0, 10, 10},
                               (Rectangle){p.pos.x - 25, p.pos.y - 25, 75, 75},
                               (Vector2){0, 0},
                               0,
                               WHITE);

                Rain();

                EndDrawing();
                timer--;
            }

            char *cause_of_death;
            if (p.hp <= 0)
                cause_of_death = "destroyed by enemy";
            else
                cause_of_death = "self destruction";

            const char *score_message = TextFormat("Final Score: %i", p.points);
            const char *death_message = TextFormat("Cause of death: %s", cause_of_death);

            while (!WindowShouldClose())
            {
                BeginDrawing();
                ClearBackground(BLACK);
                Rain();
                DrawText(score_message, 400 - (MeasureText(score_message, 50) / 2), 300, 50, WHITE);
                DrawText(death_message, 400 - (MeasureText(death_message, 25) / 2), 400, 25, WHITE);
                EndDrawing();
            }
            current_menu = START_MENU;
            break;
        }
        case HELP_MENU:
        {
            break;
        }
        }
    }
    return 0;
}