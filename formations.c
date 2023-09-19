const char formations_count = 2;
CircleFormation formations[formations_count];
int current_formations = 0;

void SpawnFormation()
{
    for (int i = 0; i < formations_count; i++)
    {
        if (formations[i].exist)
            continue;

        formations[i].exist = true;

        formations[i].rotation = 0;
        formations[i].radius = GetRandomValue(20, 50);
        formations[i].spin_speed = formations[i].radius * 0.001;
        formations[i].middle = (Vector2){GetRandomValue(100, 700), -formations[i].radius * 2};
        formations[i].target = (Vector2){GetRandomValue(formations[i].radius, GetRenderWidth() - formations[i].radius)};

        formations[i].boundary_box = (Rectangle){-formations[i].radius, -formations[i].radius, formations[i].radius * 2, formations[i].radius * 2};

        for (int j = 0; j < 4; j++)
        {
            float x = cos(formations[i].rotation + (j * (PI / 2)));
            float y = sin(formations[i].rotation + (j * (PI / 2)));

            formations[i].formation_members[j].pos = (Vector2){x, y};

            formations[i].formation_members[j].exist = true;
        }

        break;
    }
}

void UpdateFormations()
{
    for (int i = 0; i < formations_count; i++)
    {
        if (!formations[i].exist)
            continue;

        formations[i].boundary_box = (Rectangle){formations[i].middle.x - formations[i].radius, formations[i].middle.y - formations[i].radius, formations[i].radius * 2, formations[i].radius * 2};

        bool hit_target = (formations[i].middle.x == formations[i].target.x && formations[i].middle.y == formations[i].target.y);

        if (hit_target)
        {
            int start_x;

            bool right_half = i == 0 ? false : true; // If the formation has index 0 it is the left formation, starting at 0
            if (right_half)
                start_x = 400;
            else
                start_x = 0;

            formations[i].target = (Vector2){GetRandomValue(start_x + formations[i].boundary_box.width, start_x + 400 - formations[i].boundary_box.width), GetRandomValue(formations[i].boundary_box.height, 400)};
        }

        bool has_members = false;
        for (int j = 0; j < 4; j++)
        {
            if (formations[i].formation_members[j].exist)
            {
                float x = cos(formations[i].rotation + (j * (PI / 2))) * formations[i].radius;
                float y = sin(formations[i].rotation + (j * (PI / 2))) * formations[i].radius;

                formations[i].formation_members[j].pos = (Vector2){x, y};

                has_members = true;
            }
        }

        formations[i].exist = has_members;

        formations[i].rotation += formations[i].spin_speed;

        formations[i].middle = Vector2MoveTowards(formations[i].middle, formations[i].target, 0.5);
    }
}

void CheckFormationMembersHit(Player *p)
{
    for (int i = 0; i < formations_count; i++)
    {
        // Check that the formation exists
        if (!formations[i].exist)
            continue;

        // Check if any bullet hits
        for (int j = 0; j < 20; j++)
        {
            // Check if the bullet exists
            if (!p->projectiles[j].exist)
                continue;

            Rectangle projectile = (Rectangle){p->projectiles[j].pos.x, p->projectiles[j].pos.y, projectile_texture.width, projectile_texture.height};

            for (int k = 0; k < 4; k++)
            {
                // Check if the enemy exists
                if (!formations[i].formation_members[k].exist)
                    continue;

                Rectangle enemy_member = (Rectangle){formations[i].middle.x + formations[i].formation_members[k].pos.x, formations[i].middle.y + formations[i].formation_members[k].pos.y, enemy_texture.width, enemy_texture.height};

                if (CheckCollisionRecs(projectile, enemy_member))
                {
                    p->projectiles[j].exist = false;
                    formations[i].formation_members[k].exist = false;
                    p->points++;
                }
            }
        }
    }
}

void RenderFormations()
{
    for (int i = 0; i < formations_count; i++)
    {
        if (!formations[i].exist)
            continue;

        for (int j = 0; j < 4; j++)
        {
            if (!formations[i].formation_members[j].exist)
                continue;

            DrawTexture(enemy_texture, formations[i].middle.x + formations[i].formation_members[j].pos.x, formations[i].middle.y + formations[i].formation_members[j].pos.y, WHITE);
        }
    }
}