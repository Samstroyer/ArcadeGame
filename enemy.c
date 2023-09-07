#include "structs.c"
#include <stdio.h>

const int max_enemy_spawn_cooldown = 300;
const int enemy_max = 5;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

void Setup(Enemy *enemies, Player *p)
{
    for (int i = 0; i < 200; i++)
    {
        enemies[i].exist = false;
    }
    for (int i = 0; i < 20; i++)
    {
        p->projectiles[i].exist = false;
    }
}

void RenderEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            DrawTexture(enemy_texture, enemies[i].x, enemies[i].y, WHITE);
        }
    }
}

void MoveEnemies(Enemy *enemies, Player *p)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            // Casual moving
        }
        else if (enemies[i].spawning)
        {
        }
    }
}

void CheckEnemies(Enemy *enemies)
{
    int alive_enemies = 0;
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            alive_enemies++;
        }
    }

    printf("Amount of alive enemies: %i\n", alive_enemies);
}