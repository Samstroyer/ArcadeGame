#include <stdio.h>

// Variables for enemies
const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
const int spawn_intervall = 0;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

// Later on for AI
typedef enum Behaviours
{
    Neutral,
    Defencive,
    Aggressive
} Behaviours;

// Setup the enemy array
void Setup(Enemy *enemies, Player *p)
{
    p->points = 0;

    for (int i = 0; i < 200; i++)
    {
        enemies[i].exist = false;
        enemies[i].damage = 1;
        enemies[i].spawning = false;
        enemies[i].speed = 2;
    }
    for (int i = 0; i < 20; i++)
    {
        p->projectiles[i].exist = false;
    }
}

// Render the enemies at their positions
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

// Move the enemies
void MoveEnemies(Enemy *enemies, Player *p)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].spawning)
        {
            enemies[i].y = Lerp(enemies[i].y, spawn_target_y, 0.01);
            enemies[i].spawn_timer--;
        }
        else if (enemies[i].exist)
        {
        }
    }
}

// Spawn a enemy -- HAS A GOTO IN IT! --
void SpawnEnemies(Enemy *enemies, int alive_enemies)
{
    while (alive_enemies < enemy_max)
    {
        for (int i = 0; i < 200; i++)
        {
            if (!enemies[i].exist)
            {
                enemies[i].exist = true;
                enemies[i].spawning = true;
                enemies[i].x = GetRandomValue(100, 700);
                enemies[i].spawn_timer = max_enemy_spawn_cooldown;
                enemies[i].y = -100;
                // (enemies[i].speed) Remember to maybe change this?
                goto LoopEnd;
            }
        }

    LoopEnd:
        alive_enemies++;
    }
}

// Check if the enemies are dead
void CheckEnemies(Enemy *enemies)
{
    int alive_enemies = 0;
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            alive_enemies++;

            if (enemies[i].spawning)
            {
                if (enemies[i].spawn_timer <= 0)
                {
                    enemies[i].spawning = false;
                }
            }
        }
    }

    SpawnEnemies(enemies, alive_enemies);
}