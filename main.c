/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Raycaster main
 *
 *        Version:  1.0
 *        Created:  17/03/18 00:30:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "camera.h"

/*
int main(int argc, char** argv) {
    vec3d origin = {0,0,0}, ray_vector = {1,0,0};
    tri3d triangle;
    triangle.p0 = (vec3d){1.22501,  -1, 1.5};
    triangle.p1 = (vec3d){3,  -1,  -1};
    triangle.p2 = (vec3d){3, 1.5,  -1};

    tri3d_print(triangle);

    vec3d out;

    if (ray_intersect_tri(origin, ray_vector, &triangle, &out)) {
        printf("Hit at position:\n");
        vec3d_print(out);
    }
 
    return 0;
}
*/

int main() {
    camera cam = {
        .origin = (vec3d){0,0,0},
        .yaw    = 0,
        .pitch  = 0,
        .fov    = 85,
        // ..leave w and h undefined for now
        .res_x  = 800,
        .res_y  = 500
    };

    camera_calculate_w_h(&cam);

    printf("Camera:\nw: %f\nh: %f\n", cam.w, cam.h);
}
