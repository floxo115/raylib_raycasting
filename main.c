#include "raylib.h"
#include <stdlib.h>

#include "raymath.h"
#include "bernoulli.h"

const int32_t SCREEN_WIDTH = 1200;
const int32_t SCREEN_HEIGHT = 1200;
const int32_t PLAYER_WIDTH = 30;
const int32_t PLAYER_HEIGHT = 30;

const int32_t N_GRIDS = 40;

const float SPEED = 2;

typedef struct {
    double x;
    double y;
    double angle;
} Player;

void actions(Player *player) {
    if (IsKeyDown(KEY_LEFT)) {
        player->angle += 0.1;
    } else if (IsKeyDown(KEY_RIGHT)) {
        player->angle -= 0.1;
    }
    if (IsKeyDown(KEY_UP)) {
        player->y -= sin(player->angle) * SPEED;
        player->x += cos(player->angle) * SPEED;
    } else if (IsKeyDown(KEY_DOWN)) {
        player->y += sin(player->angle) * SPEED;
        player->x = cos(player->angle) * SPEED;
    }
}

void drawGrids(int height, int width, bool world[height][width]) {
    const int offset = SCREEN_HEIGHT / N_GRIDS;
    // for (int32_t i = 1; i < N_GRIDS; i++) {
    //     DrawRectangle(i * offset - 1, 0, 2, SCREEN_HEIGHT, BLUE);
    //     DrawRectangle(0, i * offset - 1, SCREEN_WIDTH, 2, BLUE);
    // }

    for (int row = 0; row < N_GRIDS; row++) {
        for (int col = 0; col < N_GRIDS; col++) {
            if (world[row][col] == true) {
                DrawRectangle(col * offset, row * offset, offset, offset, DARKBLUE);
            }
        }
    }
}

void drawPlayer(const Player *const player) {
    DrawRectangle((int) player->x, (int) player->y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);

    Vector2 sp = {
        (float) (player->x + PLAYER_WIDTH / 2.),
        (float) (player->y + PLAYER_HEIGHT / 2.),
    };
    const int32_t len_of_angle_pointer = 40;
    Vector2 ep = {(float) len_of_angle_pointer, 0};
    ep = Vector2Rotate(ep, (float) -player->angle);
    ep = Vector2Add(sp, ep);

    DrawLineEx(sp, ep, 5, YELLOW);
}


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    bool world[N_GRIDS][N_GRIDS];
    for (int c = 0; c < N_GRIDS; c++) {
        for (int r = 0; r < N_GRIDS; r++) {
            if (bernoulli(0.15) == 1) {
                world[c][r] = true;
            } else {
                world[c][r] = false;
            }
        }
    }
    for (int i = 0; i < N_GRIDS; i++) {
        world[0][i] = true;
        world[N_GRIDS - 1][i] = true;
        world[i][0] = true;
        world[i][N_GRIDS - 1] = true;
    }

    SetTargetFPS(60);

    Player player = {
        .x = (SCREEN_WIDTH / 2. - PLAYER_WIDTH / 2.),
        .y = (SCREEN_HEIGHT / 2. - PLAYER_HEIGHT / 2.),
        .angle = PI / 2,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        actions(&player);

        drawGrids(N_GRIDS, N_GRIDS, world);
        drawPlayer(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
