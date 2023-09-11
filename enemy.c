#include <stdio.h>

// Variables for enemies
const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
const int spawn_intervall = 0;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

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
        enemies[i].target_timer = 0;
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
        // If it is spawning it should move towards the spawn area
        if (enemies[i].spawning)
        {
            enemies[i].y = Lerp(enemies[i].y, spawn_target_y, 0.01);
            enemies[i].spawn_timer--;
        }
        // Else if they should move
        else if (enemies[i].exist)
        {
            // If they don't have a target they get a target here
            if (enemies[i].target_timer <= 0)
            {

                switch (enemies[i].behaviour)
                {
                case Neutral:
                    enemies[i].target.x = GetRandomValue(100, 700);
                    enemies[i].target.y = GetRandomValue(100, 500);
                    enemies[i].target_timer = 120;
                    break;
                case Aggressive:
                    enemies[i].target.x = p->x + GetRandomValue(-200, 200);
                    enemies[i].target.y = GetRandomValue(300, 400);
                    enemies[i].target_timer = 30;
                    break;
                case Dumb:
                    enemies[i].target.x = GetRandomValue(100, 700);
                    enemies[i].target.y = GetRandomValue(100, 500);
                    enemies[i].target_timer = 100;
                    break;

                default:
                    break;
                }
            }
            // Move towards the target they are assigned
            else
            {
                double lerping;

                switch (enemies[i].behaviour)
                {
                case Neutral:
                    lerping = 0.02;
                    break;
                case Aggressive:
                    lerping = 0.04;
                    break;
                case Dumb:
                    lerping = (double)(GetRandomValue(1, 3)) / 100;
                    break;
                default:
                    lerping = 0.01;
                    break;
                }

                enemies[i].x = Lerp(enemies[i].x, enemies[i].target.x, lerping);
                enemies[i].y = Lerp(enemies[i].y, enemies[i].target.y, lerping);
                enemies[i].target_timer--;
            }
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
                enemies[i].spawn_timer = max_enemy_spawn_cooldown;

                enemies[i].x = GetRandomValue(100, 700);
                enemies[i].y = -100;

                // Maybe fix different HP based on behaviour
                switch (GetRandomValue(0, 2))
                {
                case Neutral:
                    enemies[i].speed = 2;
                    enemies[i].behaviour = Neutral;
                    break;
                case Aggressive:
                    enemies[i].speed = 3;
                    enemies[i].behaviour = Aggressive;
                    break;
                case Dumb:
                    enemies[i].speed = 2;
                    enemies[i].behaviour = Dumb;
                    break;
                }
                goto SpawnEnemiesLoopEnd;
            }
        }

    SpawnEnemiesLoopEnd:
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