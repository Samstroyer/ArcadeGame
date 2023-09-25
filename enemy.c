#include <stdio.h>

// Variables for enemies
const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
const int max_spawn_interval = 400;
int spawn_interval = max_spawn_interval;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;

const short enemy_projectiles_count = 200;
Projectile enemy_projectiles[enemy_projectiles_count];

// Render the enemies at their positions
void RenderEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        if (!enemies[i].exist)
            continue;

        DrawTexture(enemy_texture, enemies[i].pos.x, enemies[i].pos.y, WHITE);
    }
}

// Makes the enemies fire projectiles based on their fire rate
void FireEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        // Check if enemy exists
        if (!enemies[i].exist)
            continue;

        if (enemies[i].fire_timer > 0)
        {
            enemies[i].fire_timer--;
        }
        else
        {
            for (int j = 0; j < enemy_projectiles_count; j++)
            {
                if (enemy_projectiles[j].exist)
                {
                    continue;
                }

                enemy_projectiles[j].exist = true;
                enemy_projectiles[j].pos = enemies[i].pos;
                enemy_projectiles[j].projectile_type = enemies[i].projectile_type;
                break;
            }
            enemies[i].fire_timer = 200;
        }
    }
}

// Moves and renders the projectiles...
void RenderEnemyProjectiles(Enemy *enemies)
{
    for (int i = 0; i < enemy_projectiles_count; i++)
    {
        if (!enemy_projectiles[i].exist)
            continue;

        enemy_projectiles[i].pos.y += 2;
        DrawTexture(projectile_texture, enemy_projectiles[i].pos.x, enemy_projectiles[i].pos.y, WHITE);
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
                    puts("Out of range Enemy.c->MoveEnemies:ln~106");
                    break;
                }

                enemies[i].target_timer = enemy_types[enemies[i].enemy_type].max_target_cooldown;
            }
            // Move towards the target they are assigned
            else
            {
                double lerp_speed = enemy_types[enemies[i].enemy_type].speed / 100;
                enemies[i].pos.x = Lerp(enemies[i].pos.x, enemies[i].target.pos.x, lerp_speed);
                enemies[i].pos.y = Lerp(enemies[i].pos.y, enemies[i].target.pos.y, lerp_speed);

                enemies[i].target_timer--;
            }
        }
    }
}

// Spawn a enemy -- HAS A GOTO IN IT! --
void SpawnEnemies(Enemy *enemies, int alive_enemies)
{
    if (alive_enemies >= enemy_max)
        return;

    int enemies_to_spawn = GetRandomValue(1, 4);

    while (enemies_to_spawn > 0)
    {
        // DEBUG LINE
        goto SpawnEnemiesLoopEnd;
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
        enemies_to_spawn--;
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

    if (spawn_interval <= 0)
    {
        SpawnEnemies(enemies, alive_enemies);

        SpawnFormation();
        // if (GetRandomValue(1, 10) == 1 && current_circle_formations < 4)
        // {
        //     current_circle_formations++;
        // }

        spawn_interval = GetRandomValue(max_spawn_interval - 120, max_spawn_interval);
    }
    else
    {
        spawn_interval--;
    }
}