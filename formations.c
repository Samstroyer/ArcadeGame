const char max_formations_general = 2;
CircleFormation circle_formations[max_formations_general];
char current_circle_formations = 0;
SnakeFormation snake_formations[max_formations_general];
char current_snake_formations = 0;

void SpawnFormation()
{
    for (int i = 0; i < max_formations_general; i++)
    {
        if (circle_formations[i].exist)
            continue;

        circle_formations[i].exist = true;

        circle_formations[i].rotation = 0;
        circle_formations[i].radius = GetRandomValue(40, 80);
        circle_formations[i].spin_speed = circle_formations[i].radius * 0.0005;
        circle_formations[i].middle = (Vector2){GetRandomValue(100, 700), -circle_formations[i].radius * 2};
        circle_formations[i].target = (Vector2){GetRandomValue(circle_formations[i].radius, GetRenderWidth() - circle_formations[i].radius)};

        circle_formations[i].boundary_box = (Rectangle){-circle_formations[i].radius, -circle_formations[i].radius, circle_formations[i].radius * 2, circle_formations[i].radius * 2};

        for (int j = 0; j < 4; j++)
        {
            float x = cos(circle_formations[i].rotation + (j * (PI / 2)));
            float y = sin(circle_formations[i].rotation + (j * (PI / 2)));

            circle_formations[i].formation_members[j].pos = (Vector2){x, y};

            circle_formations[i].formation_members[j].exist = true;
        }

        break;
    }
}

void UpdateFormations()
{
    for (int i = 0; i < max_formations_general; i++)
    {
        if (!circle_formations[i].exist)
            continue;

        circle_formations[i].boundary_box = (Rectangle){circle_formations[i].middle.x - circle_formations[i].radius, circle_formations[i].middle.y - circle_formations[i].radius, 25 + circle_formations[i].radius * 2, 25 + circle_formations[i].radius * 2};

        bool hit_target = (circle_formations[i].middle.x == circle_formations[i].target.x && circle_formations[i].middle.y == circle_formations[i].target.y);

        if (hit_target)
        {
            int start_x;

            bool right_half = i == 0 ? false : true; // If the formation has index 0 it is the left formation, starting at 0
            if (right_half)
                start_x = 400;
            else
                start_x = 0;

            circle_formations[i].target = (Vector2){GetRandomValue(start_x + circle_formations[i].boundary_box.width, start_x + 400 - circle_formations[i].boundary_box.width), GetRandomValue(circle_formations[i].boundary_box.height, 400)};
        }

        bool has_members = false;
        for (int j = 0; j < 4; j++)
        {
            if (circle_formations[i].formation_members[j].exist)
            {
                float x = cos(circle_formations[i].rotation + (j * (PI / 2))) * circle_formations[i].radius;
                float y = sin(circle_formations[i].rotation + (j * (PI / 2))) * circle_formations[i].radius;

                circle_formations[i].formation_members[j].pos = (Vector2){x, y};

                has_members = true;
            }
        }

        circle_formations[i].exist = has_members;

        circle_formations[i].rotation += circle_formations[i].spin_speed;

        circle_formations[i].middle = Vector2MoveTowards(circle_formations[i].middle, circle_formations[i].target, 1);
    }
}

void CheckFormationMembersHit(Player *p)
{
    for (int i = 0; i < max_formations_general; i++)
    {
        // Check that the formation exists
        if (!circle_formations[i].exist)
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
                if (!circle_formations[i].formation_members[k].exist)
                    continue;

                if (!CheckCollisionRecs(projectile, circle_formations[i].boundary_box))
                    continue;

                Rectangle enemy_member = (Rectangle){circle_formations[i].middle.x + circle_formations[i].formation_members[k].pos.x, circle_formations[i].middle.y + circle_formations[i].formation_members[k].pos.y, enemy_texture.width, enemy_texture.height};

                if (CheckCollisionRecs(projectile, enemy_member))
                {
                    p->projectiles[j].exist = false;
                    circle_formations[i].formation_members[k].exist = false;
                    p->points++;
                }
            }
        }
    }
}

void RenderFormations()
{
    for (int i = 0; i < max_formations_general; i++)
    {
        if (!circle_formations[i].exist)
            continue;

        for (int j = 0; j < 4; j++)
        {
            if (!circle_formations[i].formation_members[j].exist)
                continue;

            DrawTexture(enemy_texture, circle_formations[i].middle.x + circle_formations[i].formation_members[j].pos.x, circle_formations[i].middle.y + circle_formations[i].formation_members[j].pos.y, WHITE);
        }
    }
}