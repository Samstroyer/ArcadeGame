#include "structs.c"

const int max_enemy_spawn_cooldown = 300;
int enemy_max = 5, enemy_spawn_cooldown = max_enemy_spawn_cooldown;
Texture2D enemy_texture;

void Setup(Enemy *enemies, Player *p)
{
    for (int i = 0; i < 200; i++)
    {
        enemies[i].exist = false;
        enemies[i].y_switch = false;
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

    if (enemy_max > alive_enemies)
    {
        int amount_to_spawn = GetRandomValue(1, 5);
        switch (amount_to_spawn)
        {
        case 5:
            amount_to_spawn = GetRandomValue(4, 5);
            break;

        case 4:
            amount_to_spawn = GetRandomValue(3, 4);
            break;
        }

        int positions[amount_to_spawn];
        int min_size_between;

        for (int i = 0; i < amount_to_spawn; i++)
        {
            for (int j = 0; j < 200; j++)
            {
                if (!enemies[j].exist)
                {
                    enemies[j].exist = true;
                    int x = GetRandomValue(100, 700);
                    positions[i] = x;

                    if (i < 1)
                        continue;

                    for (int k = 0; k < i - 1; k++)
                    {
                        int difference = positions[k] < positions[k + 1] ? positions[k + 1] - positions[k] : positions[k] - positions[k + 1];
                        if (difference <= 50)
                        {
                            positions[k + 1] = GetRandomValue(100, 700);
                            k--;
                        }
                    }

                    enemies[j].x = positions[amount_to_spawn];
                    enemies[j].y = 400;

                    break;
                }
            }
        }
    }
}