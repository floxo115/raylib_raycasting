#include <stdio.h>

#include "raylib.h"
#include <stdlib.h>

#include "raymath.h"
#include "bernoulli.h"
#include "utils.h"

const int32_t SCREEN_WIDTH = 1200;
const int32_t SCREEN_HEIGHT = 1200;
const int32_t PLAYER_WIDTH = 15;
const int32_t PLAYER_HEIGHT = 15;

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
        player->x -= cos(player->angle) * SPEED;
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
    DrawCircle((int) player->x, (int) player->y, (float) PLAYER_HEIGHT, RED);

    Vector2 sp = {
        (float) (player->x),
        (float) (player->y),
    };
    const int32_t len_of_angle_pointer = 40;
    Vector2 ep = {(float) len_of_angle_pointer, 0};
    ep = Vector2Rotate(ep, (float) -player->angle);
    ep = Vector2Add(sp, ep);

    DrawLineEx(sp, ep, 5, YELLOW);
}

void drawRay(MyRay ray) {
    Vector2 start_ray = {(float) ray.pos_x, (float) ray.pos_y};
    Vector2 end_ray = {1, 0};
    end_ray = Vector2Scale(end_ray, (float) ray.distance);
    end_ray = Vector2Rotate(end_ray, (float) -(ray.angle));
    end_ray = Vector2Add(start_ray, end_ray);
    DrawLineEx(start_ray, end_ray, 3, GREEN);
}


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    bool world[N_GRIDS][N_GRIDS];
    for (int c = 0; c < N_GRIDS; c++) {
        for (int r = 0; r < N_GRIDS; r++) {
            if (bernoulli(0.08) == 1) {
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

    SetTargetFPS(30);

    Player player = {
        .x = (SCREEN_WIDTH / 2. - PLAYER_WIDTH / 2.),
        .y = (SCREEN_HEIGHT / 2. - PLAYER_HEIGHT / 2.),
        .angle = PI / 2,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        actions(&player);

        drawGrids(N_GRIDS, N_GRIDS, world);

        for (size_t i = 0; i < 60; i++) {
            double angle_offset = (PI * 0.95) / 120;
            MyRay ray = cast_ray(SCREEN_WIDTH, SCREEN_HEIGHT, player.y, player.x, player.angle,
                                 angle_offset * (double) i, N_GRIDS, world);
            drawRay(ray);
            ray = cast_ray(SCREEN_WIDTH, SCREEN_HEIGHT, player.y, player.x, player.angle, -(angle_offset * (double) i),
                           N_GRIDS, world);
            drawRay(ray);
        }

        drawPlayer(&player);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
