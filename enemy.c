#include <stdio.h>

// Variables for enemies
const int max_enemy_spawn_cooldown = 200;
const int enemy_max = 5;
const int spawn_target_y = 400;
const int max_spawn_interval = 300;
int spawn_interval = max_spawn_interval;
int enemy_spawn_cooldown = max_enemy_spawn_cooldown;

Projectile enemy_projectiles[500];

CircleFormation formations[4];
int current_formations = 0;

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
            // Shoot if the time has come
            if (enemies[i].fire_timer <= 0)
            {
                for (int j = 0; j < 500; j++)
                {
                    if (!enemy_projectiles[j].exist)
                    {
                        enemy_projectiles[j].exist = true;

                        enemy_projectiles[j].pos = enemies[i].pos;
                        enemy_projectiles[j].projectile_type = enemies[i].projectile_type;
                        break;
                    }
                }
                enemies[i].fire_timer = 200;
            }
            // Else you count the time til the time comes
            else
            {
                enemies[i].fire_timer--;
            }
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
            DrawTexture(projectile_texture, enemy_projectiles[i].pos.x, enemy_projectiles[i].pos.y, WHITE);
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

void SpawnFormation()
{
    for (int i = 0; i < 4; i++)
    {
        if (!formations[i].exist)
        {
            formations[i].exist = true;

            formations[i].rotation = 0;
            formations[i].radius = GetRandomValue(20, 50);
            formations[i].spin_speed = formations[i].radius * 0.001;
            formations[i].middle = (Vector2){GetRandomValue(100, 700), -10};
            formations[i].target = (Vector2){GetRandomValue(formations[i].radius, GetRenderWidth() - formations[i].radius)};

            for (int j = 0; j < 4; j++)
            {
                float x = cos(formations[i].rotation + (j * (PI / 2)));
                float y = sin(formations[i].rotation + (j * (PI / 2)));

                formations[i].formation_members[j].pos = (Vector2){x, y};

                formations[i].formation_members[j].exist = true;
            }

            goto FormationSpawnLoopBreak;
        }
    }
FormationSpawnLoopBreak:
    return;
}

void UpdateFormations()
{
    for (int i = 0; i < 4; i++)
    {
        if (formations[i].exist)
        {
            if (formations[i].middle.x == formations[i].target.x && formations[i].middle.y == formations[i].target.y)
            {
                formations[i].target = (Vector2){GetRandomValue(formations[i].radius, GetRenderWidth() - formations[i].radius), GetRandomValue(formations[i].radius, 500 - formations[i].radius)};
            }

            bool has_members = false;
            for (int j = 0; j < 4; j++)
            {
                if (formations[i].formation_members[j].exist)
                {
                    float x = cos(formations[i].rotation + (j * (PI / 2))) * formations[i].radius;
                    float y = sin(formations[i].rotation + (j * (PI / 2))) * formations[i].radius;

                    formations[i].formation_members[j].pos = (Vector2){x, y};

                    has_members = true;
                }
            }

            formations[i].exist = has_members;

            formations[i].rotation += formations[i].spin_speed;

            formations[i].middle = Vector2MoveTowards(formations[i].middle, formations[i].target, 0.5);
        }
    }
}

void CheckFormationMembersHit(Player *p)
{
    for (int i = 0; i < 4; i++)
    {
        if (formations[i].exist)
        {
            for (int j = 0; j < 20; j++)
            {
                if (p->projectiles[j].exist)
                {
                    Rectangle projectile = (Rectangle){p->projectiles[j].pos.x, p->projectiles[j].pos.y, projectile_texture.width, projectile_texture.height};

                    for (int k = 0; k < 4; k++)
                    {
                        Rectangle enemy_member = (Rectangle){formations[i].formation_members[k].pos.x, formations[i].formation_members[k].pos.y, 10, 10};

                        if (CheckCollisionRecs(projectile, enemy_member))
                        {
                            p->projectiles[j].exist = false;
                            formations[i].formation_members[k].exist = false;
                        }
                    }
                }
            }
        }
    }
}

void RenderFormations()
{
    for (int i = 0; i < 4; i++)
    {
        if (formations[i].exist)
        {
            for (int j = 0; j < 4; j++)
            {
                if (formations[i].formation_members[j].exist)
                {
                    DrawTexture(enemy_texture, formations[i].middle.x + formations[i].formation_members[j].pos.x, formations[i].middle.y + formations[i].formation_members[j].pos.y, WHITE);
                }
            }
        }
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
        // if (GetRandomValue(1, 10) == 1 && current_formations < 4)
        // {
        //     current_formations++;
        // }

        spawn_interval = GetRandomValue(max_spawn_interval - 60, max_spawn_interval + 60);
    }
    else
    {
        spawn_interval--;
    }
}