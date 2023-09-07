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
    Projectile projectiles[20];
} Player;

int enemy_spawn_timer_max = 180;

typedef struct
{
    float x;
    float y;
    float speed;
    float damage;
    int spawn_timer;
    bool spawning;
    bool exist;
    bool y_switch;
} Enemy;