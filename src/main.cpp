#include "Game.h"

enum GameState {
    MENU,
    PLAY
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Bullet Hell");
    SetTargetFPS(60);

    Texture2D playerTex = LoadTexture("assets/player.png");
    Texture2D asteroidTex = LoadTexture("assets/asteroid.png");
    Texture2D vortexTex = LoadTexture("assets/vortex.png");

    GameState state = MENU;
    int selectedItem = 0;
    Game game(playerTex, asteroidTex, vortexTex);

    while (!WindowShouldClose()) {
        if (state == MENU) {
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
                selectedItem = (selectedItem + 1) % 2;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedItem == 0) {
                    game = Game(playerTex, asteroidTex, vortexTex);
                    state = PLAY;
                } else {
                    CloseWindow();
                }
            }
        } else if (state == PLAY) {
            game.Update();
            if (game.player.health <= 0) {
                state = MENU;
                selectedItem = 0;
            }
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(BLACK);

        if (state == MENU) {
            DrawText("BULLET HELL", screenWidth/2 - MeasureText("BULLET HELL", 60)/2, 100, 60, WHITE);

            const char* items[] = { "Start Game", "Exit" };
            for (int i = 0; i < 2; i++) {
                Color color = (i == selectedItem) ? YELLOW : GRAY;
                int x = screenWidth/2 - MeasureText(items[i], 40)/2;
                int y = 250 + i * 60;
                DrawText(items[i], x, y, 40, color);
            }

            DrawText("Controls: WASD - move, Space - shoot", 10, screenHeight - 30, 20, DARKGRAY);
        } else if (state == PLAY) {
            game.Draw();
        }

        EndDrawing();
    }

    UnloadTexture(playerTex);
    UnloadTexture(asteroidTex);
    UnloadTexture(vortexTex);
    CloseWindow();
    return 0;
}