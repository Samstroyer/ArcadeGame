Explosion explosions[20];

void RenderExplosions()
{
    for (char i = 0; i < 20; i++)
    {
        if (explosions[i].timer > 0)
        {
            DrawRectangle(explosions[i].pos.x, explosions[i].pos.y, 10, 10, RED);
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

        // Adds a explosion at pos with 510 lifetime
        explosions[i] = (Explosion){.timer = 510, .pos = pos};
        break;
    }
}