#include "lib.hpp"
#include "Game/Game.hpp"

using namespace std;

int main()
{
    cout << "Starting the game..." << endl;

    InitWindow(Setting::windowWidth, Setting::windowHeight, "Ular Lily Lepas");

    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        game.HandleInput();

        if (Util::Delay(0.2))
        {
            Setting::allowMove = true;
            game.Update();
        }

        ClearBackground(Setting::green);
        
        DrawText(TextFormat("Score: %i", game.score), Setting::boardOffset - 5, 20, 40, Setting::darkGreen);
        DrawText("Ular Lily Lepas", Setting::boardOffset - 5, Setting::boardOffset + Setting::cellSize * Setting::cellCount + 10, 40, Setting::darkGreen);
        DrawRectangleLinesEx(Rectangle{(float)Setting::boardOffset - 5, (float)Setting::boardOffset - 5, (float)Setting::cellSize * Setting::cellCount + 10, (float)Setting::cellSize * Setting::cellCount + 10}, 5, Setting::darkGreen);
        game.Draw();

        ClearBackground(Setting::green);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}