#include "raylib.h"
#include "structs.c"

Texture2D player_texture;
Texture2D enemy_texture;

int cooldown_max = 50;
int fire_cooldown = 50;

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

void Keybinds(Player *p)
{
    float speed = p->speed;

    if (fire_cooldown < 0 && IsKeyDown(KEY_SPACE))
    {
    }

    if (IsKeyDown(KEY_W))
        p->y -= speed;
    if (IsKeyDown(KEY_S))
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

void RenderEnemies(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        if (enemies[i].alive)
        {
            DrawTexture(enemy_texture, enemies[i].x, enemies[i].y, WHITE);
        }
    }
}

void SetupEnemy(Enemy *enemies)
{
    for (int i = 0; i < 200; i++)
    {
        enemies[i].alive = false;
    }
}

int main()
{
    SetTargetFPS(60);
    InitWindow(800, 800, "Galaga 2.0");
    LoadImages();

    Enemy enemies[200];
    SetupEnemy(enemies);

    Player p;
    p.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
    p.y = GetScreenHeight() - 40;
    p.damage = 1;
    p.speed = 1.5f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Keybinds(&p);
        RenderPlayer(&p);
        RenderEnemies(enemies);

        EndDrawing();
    }

    return 0;
}