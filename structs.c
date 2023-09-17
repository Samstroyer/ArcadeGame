#include "raylib.h"

/*
    This file contains all the structs for the program
    Player, Enemy and Projectile structs, enums and type arrays
*/

typedef enum
{
    PROJECTILE_SLOW,
    PROJECTILE_FAST,
    PROJECTILE_EXPLOSIVE,
    PROJECTILE_LINGERING,
    PROJECTILE_NUM,
} ProjectileType_E;

typedef struct
{
    float damage;
    float speed;
} ProjectileTypeInfo;

ProjectileTypeInfo projectile_types[PROJECTILE_NUM] = {
    (ProjectileTypeInfo){.damage = 5, .speed = 2}, // Slow
    (ProjectileTypeInfo){.damage = 2, .speed = 4}, // Fast
    (ProjectileTypeInfo){.damage = 8, .speed = 3}, // Explosive
    (ProjectileTypeInfo){.damage = 1, .speed = 3}, // Lingering
};

typedef struct
{
    Vector2 pos;
    bool exist;
    ProjectileType_E projectile_type;
} Projectile;

typedef struct
{
    Vector2 pos;
    float speed;
    Projectile projectiles[20];
    char selected_projectile;
    long points;
} Player;

int enemy_spawn_timer_max = 180;

typedef enum
{
    ENEMY_SLOW,
    ENEMY_FAST,
    ENEMY_EXPLOSIVE,
    ENEMY_LINGERING,
    ENEMY_NUM,
} EnemyType_E;

typedef struct
{
    Vector2 pos;
    short timer;
} EnemyTarget;

typedef struct
{
    ProjectileType_E projectile_type_e;
    short max_target_cooldown;
    short max_fire_cooldown;
    short max_spawn_timer;
    float max_hp;
    float speed;
} EnemyTypeInfo;

typedef struct
{
    ProjectileType_E projectile_type;
    EnemyType_E enemy_type;
    EnemyTarget target;
    Vector2 pos;
    short spawn_timer;
    short fire_timer;
    short target_timer;
    bool exist;
    bool spawning;
    int hp;
} Enemy;

EnemyTypeInfo enemy_types[ENEMY_NUM] = {
    (EnemyTypeInfo){.max_spawn_timer = 300, .max_hp = 100, .speed = 2, .projectile_type_e = PROJECTILE_SLOW, .max_fire_cooldown = 100, .max_target_cooldown = 180},     // Slow
    (EnemyTypeInfo){.max_spawn_timer = 300, .max_hp = 50, .speed = 4, .projectile_type_e = PROJECTILE_FAST, .max_fire_cooldown = 100, .max_target_cooldown = 180},      // Fast
    (EnemyTypeInfo){.max_spawn_timer = 300, .max_hp = 20, .speed = 3, .projectile_type_e = PROJECTILE_EXPLOSIVE, .max_fire_cooldown = 100, .max_target_cooldown = 30},  // Explosive
    (EnemyTypeInfo){.max_spawn_timer = 300, .max_hp = 20, .speed = 3, .projectile_type_e = PROJECTILE_LINGERING, .max_fire_cooldown = 100, .max_target_cooldown = 180}, // Lingering
};

typedef struct
{
    Vector2 pos;
    bool exist;
} FormationEnemy;

typedef struct
{
    Vector2 middle;
    Vector2 velocity;
    Vector2 target;
    FormationEnemy formation_members[4];
    bool exist;
    float rotation;
    float radius;
    float spin_speed;
} CircleFormation;