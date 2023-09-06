#include "raylib.h"

typedef struct
{
    float x;
    float y;
    float damage;
    float speed;
} Player;

typedef struct
{
    float x;
    float y;
    float speed;
    float damage;
} Projectile;

typedef struct
{
    float x;
    float y;
    float speed;
    float damage;
    bool alive;
} Enemy;