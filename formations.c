const char max_formations = 4;
const char max_members = 10;
Formation formations[max_formations];
char current_formations = 0;
const unsigned char max_enemy_shooting_cooldown = 250;

const char max_formation_projectiles = 80;
FormationProjectile formation_projectiles[max_formation_projectiles];

void SpawnFormation()
{
    for (char i = 0; i < max_formations; i++)
    {
        if (formations[i].exist)
            continue;

        current_formations++;

        formations[i].exist = true;
        formations[i].member_count = GetRandomValue(3, 10);

        formations[i].timer = 0;

        formations[i].middle = (Vector2){GetRandomValue(200, 600), -200};

        formations[i].target = (Vector2){GetRandomValue(formations[i].radius, GetRenderWidth() - formations[i].radius)};

        // Make sure that no enemies exist from previous formations
        for (int j = 0; j < max_members; j++)
        {
            formations[i].formation_members[j].exist = false;
            formations[i].formation_members[j].timer = GetRandomValue(max_enemy_shooting_cooldown / 2, max_enemy_shooting_cooldown);
        }

        switch (formations[i].member_count)
        {
        case THREE_MEMBER:
        {
            formations[i].spin_speed = GetRandomValue(3, 6) * 0.01;
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 30,
                                                     formations[i].middle.y - 5,
                                                     60,
                                                     90};
            // Snake formation
            for (char j = 0; j < 3; j++)
            {
                float x = cos(formations[i].timer + j) * 20;
                formations[i].formation_members[j].pos = (Vector2){x, j * 25};
                formations[i].formation_members[j].exist = true;
            }
            break;
        }
        case FOUR_MEMBER:
        {
            formations[i].radius = GetRandomValue(40, 80);
            formations[i].spin_speed = formations[i].radius * 0.0002;
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - formations[i].radius - 5,
                                                     formations[i].middle.y - formations[i].radius - 5,
                                                     formations[i].radius * 2 + 15,
                                                     formations[i].radius * 2 + 15};
            // Spinning circle formation
            for (char j = 0; j < 4; j++)
            {
                float x = cos(formations[i].timer + (j * (PI / 2))) * formations[i].radius;
                float y = sin(formations[i].timer + (j * (PI / 2))) * formations[i].radius;

                formations[i].formation_members[j].pos = (Vector2){x, y};
                formations[i].formation_members[j].exist = true;
            }
            break;
        }
        case FIVE_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 40,
                                                     formations[i].middle.y - 5,
                                                     80,
                                                     90};
            // T formation - First ¯ then |
            char start_x = -30;
            for (char j = 0; j < 3; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){start_x, 0};
                formations[i].formation_members[j].exist = true;

                start_x += 30;
            }
            char start_y = 30;
            for (char j = 3; j < 5; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){0, start_y};
                formations[i].formation_members[j].exist = true;

                start_y += 30;
            }
            break;
        }
        case SIX_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 30,
                                                     formations[i].middle.y - 5,
                                                     60,
                                                     90};
            // Dropping fish formation
            char start_x = -20;
            for (char j = 0; j < 2; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){start_x, 0};
                formations[i].formation_members[j].exist = true;
                formations[i].formation_members[j + 2].pos = (Vector2){start_x, 40};
                formations[i].formation_members[j + 2].exist = true;
                start_x += 40;
            }

            formations[i].formation_members[4].pos = (Vector2){0, 20};
            formations[i].formation_members[4].exist = true;
            formations[i].formation_members[5].pos = (Vector2){0, 60};
            formations[i].formation_members[5].exist = true;
            break;
        }
        case SEVEN_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 100,
                                                     formations[i].middle.y - 5,
                                                     200,
                                                     100};
            // Square root formation
            char start_x = -85;
            for (char j = 0; j < 2; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){start_x, 0};
                formations[i].formation_members[j].exist = true;
                formations[i].formation_members[j + 2].pos = (Vector2){start_x + 145, 0};
                formations[i].formation_members[j + 2].exist = true;
                start_x += 25;
            }
            formations[i].formation_members[4].pos = (Vector2){-40, 35};
            formations[i].formation_members[4].exist = true;
            formations[i].formation_members[5].pos = (Vector2){40, 35};
            formations[i].formation_members[5].exist = true;

            formations[i].formation_members[6].pos = (Vector2){0, 70};
            formations[i].formation_members[6].exist = true;

            break;
        }
        case EIGHT_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 70,
                                                     formations[i].middle.y - 5,
                                                     140,
                                                     90};
            // Large circle formation
            for (char j = 0; j < 8; j++)
            {
                float x = cos(formations[i].timer + (j * (PI / 4))) * 60;
                float y = sin(formations[i].timer + (j * (PI / 4))) * 60;

                formations[i].formation_members[j].pos = (Vector2){x, y};
                formations[i].formation_members[j].exist = true;
            }
            break;
        }
        case NINE_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 60,
                                                     formations[i].middle.y - 5,
                                                     120,
                                                     120};
            // Crazy cube formation
            char start_x = -40;
            for (char j = 0; j < 3; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){start_x, 0};
                formations[i].formation_members[j].exist = true;

                formations[i].formation_members[j + 3].pos = (Vector2){start_x, 40};
                formations[i].formation_members[j + 3].exist = true;

                formations[i].formation_members[j + 6].pos = (Vector2){start_x, 80};
                formations[i].formation_members[j + 6].exist = true;

                start_x += 40;
            }
            break;
        }
        case TEN_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 100,
                                                     formations[i].middle.y - 5,
                                                     200,
                                                     160};
            char start_y = 0;
            for (char j = 0; j < 2; j++)
            {
                formations[i].formation_members[j].pos = (Vector2){-90, start_y};
                formations[i].formation_members[j].exist = true;
                formations[i].formation_members[j + 2].pos = (Vector2){90, start_y};
                formations[i].formation_members[j + 2].exist = true;

                formations[i].formation_members[j + 4].pos = (Vector2){-60, start_y + 90};
                formations[i].formation_members[j + 4].exist = true;
                formations[i].formation_members[j + 6].pos = (Vector2){60, start_y + 90};
                formations[i].formation_members[j + 6].exist = true;

                start_y += 50;
            }

            formations[i].formation_members[8].pos = (Vector2){0, 20};
            formations[i].formation_members[8].exist = true;

            formations[i].formation_members[9].pos = (Vector2){0, 120};
            formations[i].formation_members[9].exist = true;
            break;
        }
        default:
        {
            puts("Error in formations.c at ~ ln 180");
            break;
        }
        }

        formations[i].boundary_box = (Rectangle){-formations[i].radius, -formations[i].radius, formations[i].radius * 2, formations[i].radius * 2};

        // Need to use the box for this v
        break;
    }
}

void UpdateFormations()
{
    for (char i = 0; i < max_formations; i++)
    {
        if (!formations[i].exist)
            continue;

        bool has_members = false;
        for (char j = 0; j < 10; j++)
        {
            has_members = formations[i].formation_members[j].exist ? true : has_members;
        }
        formations[i].exist = has_members;

        if (!formations[i].exist)
        {
            current_formations--;
            continue;
        }

        // Get a new target if previous target has been located
        if (Vector2Equals(formations[i].middle, formations[i].target))
            formations[i].target = (Vector2){
                GetRandomValue(formations[i].boundary_box.width, GetScreenWidth() - formations[i].boundary_box.width),
                GetRandomValue(formations[i].boundary_box.height, 550 - formations[i].boundary_box.height)};

        // This switch is mostly for calculating hitboxes
        switch (formations[i].member_count)
        {
        case THREE_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 30,
                                                     formations[i].middle.y - 5,
                                                     80,
                                                     90};
            // Snake formation
            for (char j = 0; j < formations[i].member_count; j++)
            {
                float x = cos(formations[i].timer + j) * 20;
                formations[i].formation_members[j].pos = (Vector2){x, j * 20};
            }
            break;
        }
        case FOUR_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - formations[i].radius - 5,
                                                     formations[i].middle.y - formations[i].radius - 40,
                                                     formations[i].radius * 2 + 30,
                                                     formations[i].radius * 2 + 60};
            // Spinning circle formation
            for (char j = 0; j < formations[i].member_count; j++)
            {
                if (formations[i].formation_members[j].exist)
                {
                    float x = cos(formations[i].timer + (j * (PI / 2))) * formations[i].radius;
                    float y = sin(formations[i].timer + (j * (PI / 2))) * formations[i].radius;
                    formations[i].formation_members[j].pos = (Vector2){x, y};
                }
            }
            break;
        }
        case FIVE_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 40,
                                                     formations[i].middle.y - 5,
                                                     100,
                                                     90};
            break;
        }
        case SIX_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 30,
                                                     formations[i].middle.y - 5,
                                                     80,
                                                     90};
            break;
        }
        case SEVEN_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 100,
                                                     formations[i].middle.y - 5,
                                                     220,
                                                     100};
            break;
        }
        case EIGHT_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 70,
                                                     formations[i].middle.y - 80,
                                                     160,
                                                     180};
            break;
        }
        case NINE_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 60,
                                                     formations[i].middle.y - 5,
                                                     140,
                                                     120};
            break;
        }
        case TEN_MEMBER:
        {
            formations[i].boundary_box = (Rectangle){formations[i].middle.x - 100,
                                                     formations[i].middle.y - 5,
                                                     220,
                                                     160};
            break;
        }
        default:
        {
            puts("Error in formations.c at ~ ln 120");
            break;
        }
        }

        // DrawRectangleRec(formations[i].boundary_box, RED); // Draws bounding boxes

        formations[i].timer += formations[i].spin_speed;

        formations[i].middle = Vector2MoveTowards(formations[i].middle, formations[i].target, 1);
    }
}

void CheckFormationMembersHit(Player *p)
{
    for (char i = 0; i < max_formations; i++)
    {
        // Check that the formation exists
        if (!formations[i].exist)
            continue;

        // Check if any bullet hits
        for (char j = 0; j < 20; j++)
        {
            // Check if the bullet exists
            if (!p->projectiles[j].exist)
                continue;

            Rectangle projectile = (Rectangle){p->projectiles[j].pos.x, p->projectiles[j].pos.y, projectile_texture.width, projectile_texture.height};

            if (!CheckCollisionRecs(projectile, formations[i].boundary_box))
                continue;

            for (char k = 0; k < 10; k++)
            {
                // Check if the enemy exists
                if (!formations[i].formation_members[k].exist)
                    continue;

                // if (!CheckCollisionRecs(projectile, formations[i].boundary_box))
                //     continue;

                Rectangle enemy_member = (Rectangle){
                    formations[i].middle.x + formations[i].formation_members[k].pos.x,
                    formations[i].middle.y + formations[i].formation_members[k].pos.y,
                    enemy_texture.width,
                    enemy_texture.height};

                if (CheckCollisionRecs(projectile, enemy_member))
                {
                    AddExplosion(Vector2Add(formations[i].middle, formations[i].formation_members[k].pos));
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
    for (int i = 0; i < max_formations; i++)
    {
        if (!formations[i].exist)
            continue;

        for (int j = 0; j < 10; j++)
        {
            if (!formations[i].formation_members[j].exist)
                continue;

            DrawTexture(enemy_texture, formations[i].middle.x + formations[i].formation_members[j].pos.x, formations[i].middle.y + formations[i].formation_members[j].pos.y, WHITE);
        }
    }
}

void FormationsShoot()
{
    for (int i = 0; i < max_formations; i++)
    {
        if (!formations[i].exist)
            continue;

        for (int j = 0; j < max_members; j++)
        {
            if (!formations[i].formation_members[j].exist)
                continue;

            if (formations[i].formation_members[j].timer > 0)
            {
                formations[i].formation_members[j].timer--;
            }
            else
            {
                // make it nor fire always
                if (GetRandomValue(0, 10) > 8)
                {
                    for (int k = 0; k < max_formation_projectiles; k++)
                    {
                        if (formation_projectiles[k].exist)
                            continue;

                        formation_projectiles[k].exist = true;
                        formation_projectiles[k].pos = Vector2Add(formations[i].formation_members[j].pos, formations[i].middle);
                        break;
                    }
                }
                formations[i].formation_members[j].timer = GetRandomValue(max_enemy_shooting_cooldown / 2, max_enemy_shooting_cooldown);
            }
        }
    }
}

void UpdateAndDrawFormationProjectiles()
{
    for (int i = 0; i < max_formation_projectiles; i++)
    {
        if (!formation_projectiles[i].exist)
            continue;

        if (formation_projectiles[i].pos.y > 800)
        {
            formation_projectiles[i].exist = false;
        }
        else
        {
            formation_projectiles[i].pos.y += 3;
            DrawTexture(projectile_texture, formation_projectiles[i].pos.x, formation_projectiles[i].pos.y, PURPLE);
        }
    }
}

// void ReformatFormation() {}