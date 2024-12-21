#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

typedef struct {
    int row;
    int col;
} WorldIndex;

typedef struct {
    double distance;
    double angle;
    double pos_y;
    double pos_x;
} MyRay;

WorldIndex get_worldindex_from_pos(int width, int height, int n_grids, int pos_y, int pos_x);

void print_worldindex(WorldIndex world_index);

MyRay cast_ray(int world_width, int world_height, double start_y, double start_x, double player_angle, double ray_angle,
               int n_grids, bool world[n_grids][n_grids]);

#endif //UTILS_H
