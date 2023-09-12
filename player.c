#include <stdio.h>

// Player texture
Texture2D player_texture;
Texture2D projectile_texture;

// The cooldown on weapon
const int cooldown_max = 50;
int fire_cooldown = cooldown_max;

// Spawns a projectile at player
void Fire(Player *p)
{
    for (int i = 0; i < 20; i++)
    {
        if (!p->projectiles[i].exist)
        {
            p->projectiles[i].exist = true;
            p->projectiles[i].x = p->x + 8;
            p->projectiles[i].y = p->y;
            p->projectiles[i].damage = p->damage;
            break;
        }
    }
}

// Check for input - Movement and firing
void Input(Player *p)
{
    float speed = p->speed;
    speed = IsKeyDown(KEY_LEFT_SHIFT) ? speed * 2 : speed;

    if (p->x < 0)
    {
        p->x = GetScreenWidth() - player_texture.width;
    }
    else if (p->x + player_texture.width > GetScreenWidth())
    {
        p->x = 0;
    }

    bool limit_up = false, limit_down = false;
    if (p->y + player_texture.height >= GetScreenHeight())
    {
        limit_down = true;
    }
    else if (p->y <= 600)
    {
        limit_up = true;
    }

    if (fire_cooldown <= 0 && IsKeyDown(KEY_SPACE))
    {
        fire_cooldown = cooldown_max;
        Fire(p);
    }
    else if (fire_cooldown > 0)
    {
        fire_cooldown--;
    }

    if (IsKeyDown(KEY_W) && !limit_up)
        p->y -= speed;
    if (IsKeyDown(KEY_S) && !limit_down)
        p->y += speed;
    if (IsKeyDown(KEY_A))
        p->x -= speed;
    if (IsKeyDown(KEY_D))
        p->x += speed;
}

// Render the player
void RenderPlayer(Player *p)
{
    DrawTexture(player_texture, p->x, p->y, WHITE);
}

// Update all the projectiles the player has shot
void UpdateProjectiles(Player *p)
{
    for (int i = 0; i < 20; i++)
    {
        if (p->projectiles[i].exist)
        {
            p->projectiles[i].y -= 3.5;
            DrawTexture(projectile_texture, p->projectiles[i].x, p->projectiles[i].y, WHITE);
            if (p->projectiles[i].y <= -10)
            {
                p->projectiles[i].exist = false;
            }
        }
    }
}

void CheckProjectileCollisions(Enemy *enemies, Player *p)
{
    int enemy_sprite_width = enemy_texture.width;
    int enemy_sprite_height = enemy_texture.height;

    int player_sprite_width = player_texture.width;
    int player_sprite_height = player_texture.height;

    for (int i = 0; i < 200; i++)
    {
        if (!enemies[i].exist)
            continue;

        for (int j = 0; j < 20; j++)
        {
            if (!p->projectiles[j].exist)
                continue;

            Rectangle enemy = {enemies[i].x, enemies[i].y, enemy_sprite_width, enemy_sprite_height};
            Rectangle projectile = {p->projectiles[j].x, p->projectiles[j].y, 10, 10};

            if (CheckCollisionRecs(enemy, projectile))
            {
                p->projectiles[j].exist = false;
                enemies[i].exist = false;
                p->points++;
            }
        }
    }
}