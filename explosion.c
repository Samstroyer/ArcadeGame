Explosion explosions[20];
const short explosion_life_time = 60;

void RenderExplosions()
{
    for (char i = 0; i < 20; i++)
    {
        if (explosions[i].timer > 0)
        {
            int sprite_number = Remap(explosions[i].timer, 0, explosion_life_time, 3, 0);
            DrawTexturePro(
                explosion_texture,
                (Rectangle){sprite_number * 10, 0, 10, 10},
                (Rectangle){explosions[i].pos.x, explosions[i].pos.y, 25, 25},
                (Vector2){0, 0},
                0,
                WHITE);
            explosions[i].timer--;
        }
    }
}

void AddExplosion(Vector2 pos)
{
    for (char i = 0; i < 20; i++)
    {
        if (explosions[i].timer > 0)
            continue;

        // Adds an explosion at pos with life time of explosion_lite_time
        explosions[i] = (Explosion){.timer = explosion_life_time, .pos = pos};
        break;
    }
}