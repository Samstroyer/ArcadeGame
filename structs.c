#include "raylib.h"

typedef struct
{
    float x;
    float y;
    float damage;
    bool exist;
} Projectile;

typedef struct
{
    float x;
    float y;
    float damage;
    float speed;
    Projectile projectiles[200];
} Player;

typedef struct
{
    float x;
    float y;
    float speed;
    float damage;
    bool exist;
} Enemy;