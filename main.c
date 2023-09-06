#include "raylib.h"

typedef struct
{
    float x;
    float y;
    float damage;
    float speed;
} Player;

Texture2D player_texture;
Texture2D enemy_texture;

void LoadImages()
{
    Image player_image = LoadImage("Sprites/player.png");
    Image enemy_image = LoadImage("Sprites/player.png");

    ImageResize(&player_image, 25, 25);
    ImageResize(&enemy_image, 25, 25);

    player_texture = LoadTextureFromImage(player_image);
    enemy_texture = LoadTextureFromImage(enemy_image);

    UnloadImage(player_image);
    UnloadImage(enemy_image);
}

void Movement(Player *p)
{
    float speed = p->speed;

    if (IsKeyDown(KEY_W))
        p->y -= speed;
    if (IsKeyDown(KEY_S))
        p->y += speed;
    if (IsKeyDown(KEY_A))
        p->x -= speed;
    if (IsKeyDown(KEY_D))
        p->x += speed;
}

int main()
{
    SetTargetFPS(60);
    InitWindow(800, 800, "Galaga 2.0");
    LoadImages();
    Player p;
    p.x = (GetScreenWidth() / 2) - (player_texture.width / 2);
    p.y = GetScreenHeight() - 40;
    p.damage = 1;
    p.speed = 1.5f;

    while (!WindowShouldClose())
    {
        Movement(&p);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(player_texture, p.x, p.y, WHITE);
        EndDrawing();
    }

    return 0;
}