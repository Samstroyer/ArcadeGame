#include <stdio.h>

const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

enum Behaviours
{
    Neutral,
    Defencive,
    Aggressive
};

void Setup(Enemy *enemies, Player *p)
{
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
        if (enemies[i].spawning)
        {
            enemies[i].y = Lerp(enemies[i].y, spawn_target_y, 0.01);
            enemies[i].spawn_timer--;
            printf("at %f at %i\n", enemies[i].y, enemies[i].spawn_timer);
        }
        else if (enemies[i].exist)
        {
        }
    }
}

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

    printf("Amount of alive enemies: %i\n", alive_enemies);
}