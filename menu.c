Rectangle start_button = (Rectangle){300, 300, 200, 50};
Rectangle exit_button = (Rectangle){300, 400, 200, 50};

Menu_E current_menu = START_MENU;

const int max_rain = 50;
Vector4 rain[max_rain];

void RenderMenu()
{
    Vector2 mouse_pos = GetMousePosition();

    BeginDrawing();
    ClearBackground(WHITE);

    DrawRectangleRec(start_button, GRAY);
    DrawRectangleLinesEx(start_button, 3, BLACK);
    DrawText("PLAY", start_button.x + 56, start_button.y + 9, 32, BLACK);

    DrawRectangleRec(exit_button, GRAY);
    DrawRectangleLinesEx(exit_button, 3, BLACK);
    DrawText("EXIT", exit_button.x + 56, exit_button.y + 9, 32, BLACK);

    if (CheckCollisionPointRec(mouse_pos, start_button))
    {
        DrawRectangleRec(start_button, LIGHTGRAY);
        DrawRectangleLinesEx(start_button, 3, BLACK);
        DrawText("PLAY", start_button.x + 56, start_button.y + 9, 32, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            current_menu = GAME_MENU;

            for (int i = 0; i < max_rain; i++)
            {
                rain[i].w = 0;
            }
        }
    }

    if (CheckCollisionPointRec(mouse_pos, exit_button))
    {
        DrawRectangleRec(exit_button, LIGHTGRAY);
        DrawRectangleLinesEx(exit_button, 3, BLACK);
        DrawText("EXIT", exit_button.x + 56, exit_button.y + 9, 32, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            exit(0);
        }
    }

    EndDrawing();
}

void Rain()
{
    for (int i = 0; i < max_rain; i++)
    {
        if (rain[i].w == 0)
            rain[i] = (Vector4){GetRandomValue(0, GetScreenWidth()), GetRandomValue(-400, -30), GetRandomValue(1, 3), 1};

        if (rain[i].y > GetScreenHeight() + 10)
            rain[i].w = 0;

        rain[i].y += rain[i].z * 1.5;

        char c_val = (rain[i].z * 20) + 50;
        DrawRectangle(rain[i].x, rain[i].y, 3, rain[i].z * 3, (Color){c_val, c_val, c_val, 255});
    }
}

void StartAnimation()
{
    int i = 255;

    Color fade = (Color){255, 255, 255, 255};

    while (i > 0)
    {
        fade = (Color){i, i, i, 255};

        BeginDrawing();

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fade);

        Rain();

        EndDrawing();

        i--;
    }
}