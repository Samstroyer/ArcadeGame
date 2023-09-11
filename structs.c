#include "raylib.h"

/*
    This file contains all the structs for the program
    Player, Enemy and Projectile structs
*/

// Later on for AI
typedef enum Behaviours
{
    Neutral,
    Defencive,
    Aggressive,
    Dumb
} Behaviours;

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
    long points;
} Player;

int enemy_spawn_timer_max = 180;

typedef struct
{
    float x;
    float y;
} EnemyTarget;

typedef struct
{
    float x;
    float y;
    float speed;
    float damage;
    int spawn_timer;
    bool spawning;
    bool exist;
    Behaviours behaviour;
    EnemyTarget target;
    int target_timer;
} Enemy;