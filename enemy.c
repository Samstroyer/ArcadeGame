#include <stdio.h>

// Variables for enemies
const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
const int spawn_intervall = 0;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

Projectile enemy_projectiles[500];

// Render the enemies at their positions
void RenderEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            DrawTexture(enemy_texture, enemies[i].pos.x, enemies[i].pos.y, WHITE);
        }
    }
}

// Makes the enemies fire projectiles based on their fire rate
void FireEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].exist)
        {
            if (enemies[i].fire_timer <= 0)
            {
                for (int j = 0; j < 500; j++)
                {
                    if (!enemy_projectiles[j].exist)
                    {
                        enemy_projectiles[j].exist = true;

                        // enemy_projectiles[j].projectile_type =
                        enemy_projectiles[j].pos = enemies[i].pos;
                        enemy_projectiles[j].projectile_type = enemies[i].projectile_type;
                    }
                }
            }
            enemies[i].fire_timer = 200;
        }
        else
        {
            enemies[i].fire_timer--;
        }
    }
}

// Moves and renders the projectiles...
void RenderEnemyProjectiles(Enemy *enemies)
{
    for (int i = 0; i < 500; i++)
    {
        if (enemy_projectiles[i].exist)
        {
            enemy_projectiles[i].pos.y += 2;
            DrawRectangle(enemy_projectiles[i].pos.x, enemy_projectiles[i].pos.y, 5, 5, RED);
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
            enemies[i].pos.y = Lerp(enemies[i].pos.y, spawn_target_y, 0.01);
            enemies[i].spawn_timer--;
        }
        // Else if they should move
        else if (enemies[i].exist)
        {
            // If they don't have a target they get a target here
            if (enemies[i].target_timer <= 0)
            {

                switch (enemies[i].enemy_type)
                {
                case ENEMY_SLOW:
                    enemies[i].target.pos = (Vector2){GetRandomValue(100, 700), GetRandomValue(100, 500)};
                    break;

                case ENEMY_FAST:
                    enemies[i].target.pos = (Vector2){GetRandomValue(100, 700), GetRandomValue(100, 500)};
                    break;

                case ENEMY_EXPLOSIVE:
                    enemies[i].target.pos = (Vector2){p->pos.x - GetRandomValue(-50, 50), GetRandomValue(300, 500)};
                    break;

                case ENEMY_LINGERING:
                    enemies[i].target.pos = (Vector2){p->pos.x - GetRandomValue(-100, 100), GetRandomValue(100, 500)};
                    break;
                default:
                    puts("Out of range Enemy.c:104");
                    break;
                }

                enemies[i].target_timer = enemy_types[enemies[i].enemy_type].max_target_cooldown;
            }
        }
        // Move towards the target they are assigned
        else
        {
            float lerp_speed = enemy_types[enemies[i].enemy_type].speed / 100;
            enemies[i].pos.x = Lerp(enemies[i].pos.x, enemies[i].target.pos.x, lerp_speed);
            enemies[i].pos.y = Lerp(enemies[i].pos.y, enemies[i].target.pos.y, lerp_speed);

            enemies[i].target_timer--;
        }
    }
}

// Spawn a enemy -- HAS A GOTO IN IT! --
void SpawnEnemies(Enemy *enemies, int alive_enemies)
{
    if (alive_enemies >= enemy_max)
        return;

    while (alive_enemies < enemy_max)
    {
        for (int i = 0; i < 200; i++)
        {
            if (!enemies[i].exist)
            {
                char type = GetRandomValue(0, ENEMY_NUM - 1);
                enemies[i].enemy_type = type;
                enemies[i].projectile_type = type;

                enemies[i].exist = true;
                enemies[i].spawning = true;

                enemies[i].pos.x = GetRandomValue(100, 700);
                enemies[i].pos.y = -100;

                enemies[i].hp = enemy_types[type].max_hp;
                enemies[i].fire_timer = enemy_types[type].max_fire_cooldown;
                enemies[i].spawn_timer = enemy_types[type].max_spawn_timer;
                enemies[i].target_timer = enemy_types[type].max_target_cooldown;
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