#include "raylib.h"
#include "enemy.c"

Texture2D player_texture;

const int cooldown_max = 50;
int fire_cooldown = cooldown_max;

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

    UnloadImage(player_image);
    UnloadImage(enemy_image);
}

void Fire(Player *p)
{
    for (int i = 0; i < 20; i++)
    {
        if (!p->projectiles[i].exist)
        {
            p->projectiles[i].exist = true;
            p->projectiles[i].x = p->x;
            p->projectiles[i].y = p->y;
            p->projectiles[i].damage = p->damage;
            break;
        }
    }
}

void Keybinds(Player *p)
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

void RenderPlayer(Player *p)
{
    DrawTexture(player_texture, p->x, p->y, WHITE);
}

void UpdateProjectiles(Player *p)
{
    for (int i = 0; i < 20; i++)
    {
        if (p->projectiles[i].exist)
        {
            p->projectiles[i].y -= 3.5;
            DrawRectangle(p->projectiles[i].x, p->projectiles[i].y, 10, 10, RED);
            if (p->projectiles[i].y <= -10)
            {
                p->projectiles[i].exist = false;
            }
        }
    }
}

int main()
{
    SetTargetFPS(60);
    InitWindow(800, 800, "Galaga 2.0");
    LoadImages();

    Enemy enemies[200];

    Player p;
    p.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
    p.y = GetScreenHeight() - 40;
    p.damage = 1;
    p.speed = 2.5f;

    Setup(enemies, &p);

    enemies[0].exist = true;
    enemies[0].x = 300;
    enemies[0].y = 300;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Keybinds(&p);
        RenderPlayer(&p);
        UpdateProjectiles(&p);
        MoveEnemies(enemies, &p);
        RenderEnemies(enemies);

        CheckEnemies(enemies);

        EndDrawing();
    }

    return 0;
}