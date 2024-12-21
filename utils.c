#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#include <math.h>
#include "raymath.h"

WorldIndex get_worldindex_from_pos(int width, int height, int n_grids, int pos_y, int pos_x) {
    if (width <= 0 || height <= 0 || n_grids <= 0 || pos_y <= 0 || pos_x <= 0) {
        fprintf(stderr, "wrong input for get_world function");
        exit(EXIT_FAILURE);
    }

    int grid_width = width / n_grids;
    int grid_height = height / n_grids;

    WorldIndex world_index;
    world_index.row = pos_y / grid_height;
    world_index.col = pos_x / grid_width;

    return world_index;
}

void print_worldindex(WorldIndex wi) {
    printf("Worldindex: %d, %d\n", wi.row, wi.col);
}


#define MAX_DISTANCE 99999

MyRay cast_ray(int world_width, int world_height, double start_y, double start_x, double player_angle, double ray_angle,
               int n_grids, bool world[n_grids][n_grids]) {
    double distance = 0;
    double speed = 0.1;

    double angle = player_angle + ray_angle;

    int i = 0;
    WorldIndex wi;
    do {
        i++;
        double new_x = start_x + cos(angle) * speed * i;
        double new_y = start_y - sin(angle) * speed * i;
        double dist_x = new_x - start_x;
        double dist_y = new_y - start_y;
        distance = sqrt(dist_x * dist_x + dist_y * dist_y);

        if (distance >= MAX_DISTANCE) {
            fprintf(stderr, "raycast distance is too long");
            exit(EXIT_FAILURE);
        }

        wi = get_worldindex_from_pos(world_width, world_height, n_grids, (int) new_y, (int) new_x);
    } while (world[wi.row][wi.col] != 1);

    MyRay ray = {.distance = distance, .pos_x = start_x, .pos_y = start_y, .angle = angle};
    return ray;
}


