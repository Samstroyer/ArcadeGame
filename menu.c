Rectangle start_button = (Rectangle){300, 300, 200, 50};
Rectangle help_button = (Rectangle){300, 400, 200, 50};
Rectangle exit_button = (Rectangle){300, 500, 200, 50};

Menu_E current_menu = START_MENU;

const int max_rain = 50;
Vector4 rain[max_rain];

void RenderMenu()
{
    Vector2 mouse_pos = GetMousePosition();

    BeginDrawing();
    ClearBackground(WHITE);

    DrawTexture(title_texture, 200, 100, WHITE);

    DrawRectangleRec(start_button, GRAY);
    DrawRectangleLinesEx(start_button, 3, BLACK);
    DrawText("PLAY", start_button.x + 56, start_button.y + 9, 32, BLACK);

    DrawRectangleRec(help_button, GRAY);
    DrawRectangleLinesEx(help_button, 3, BLACK);
    DrawText("HELP", help_button.x + 56, help_button.y + 9, 32, BLACK);

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

    if (CheckCollisionPointRec(mouse_pos, help_button))
    {
        DrawRectangleRec(help_button, LIGHTGRAY);
        DrawRectangleLinesEx(help_button, 3, BLACK);
        DrawText("HELP", help_button.x + 56, help_button.y + 9, 32, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            current_menu = HELP_MENU;
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

void HelpAnimation()
{
    float i = 255;

    Color fade = (Color){255, 255, 255, 255};

    while (i > 0)
    {
        fade = (Color){i, i, i, 255};

        BeginDrawing();

        int x = Remap(i, 255, 0, 0, GetScreenWidth());

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        DrawRectangle(x, x, GetScreenWidth() - x * 2, GetScreenHeight() - x * 2, fade);

        EndDrawing();

        i -= 1.5;
    }
}

void HelpMenu()
{
    HelpAnimation();

    char font_title = 48;
    char font_other = 24;

    char *title = "Welcome to my arcade game!";
    short title_size = MeasureText(title, font_title);

    char *line_one = "This game is created by Samuel Palmér in Te4.";
    short line_one_size = MeasureText(line_one, font_other);

    char *line_two = "The game is a verson of Galage.";
    short line_two_size = MeasureText(line_two, font_other);

    char *controls_line = "Move your ship with WASD, shoot with space.";
    short controls_line_size = MeasureText(controls_line, font_other);

    char *exit_line = "Press ESC to exit";
    short exit_line_size = MeasureText(exit_line, font_other);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText(title, GetScreenWidth() / 2 - title_size / 2, 200, font_title, WHITE);
        DrawText(line_one, GetScreenWidth() / 2 - line_one_size / 2, 300, font_other, LIGHTGRAY);
        DrawText(line_two, GetScreenWidth() / 2 - line_two_size / 2, 340, font_other, LIGHTGRAY);
        DrawText(controls_line, GetScreenWidth() / 2 - controls_line_size / 2, 380, font_other, LIGHTGRAY);
        DrawText(exit_line, GetScreenWidth() / 2 - exit_line_size / 2, 450, font_other, LIGHTGRAY);

        EndDrawing();
    }

    current_menu = START_MENU;
}