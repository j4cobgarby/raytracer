/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Raycaster main
 *
 *        Created:  17/03/18 00:30:14
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

#include "img.h"
#include "camera.h"
#include "render.h"

int main() {
    SDL_Surface* surf;
    tri3d tri1 = {
       (vec3d){2.34962, 0.21173, 0.06036},
       (vec3d){1.50993, -0.29166, -0.47957},
       (vec3d){1.64327, -0.21173, 0.62760},

       (material){.diffuse = 0x00ff0000}
    };
    camera cam = {
        .origin = (vec3d){0,0,0},
        .yaw    = 0,
        .pitch  = 0,
        .fov    = 85,
        // ..leave w and h undefined for now
        .res_x  = 800,
        .res_y  = 500
    };

    surf = create_surface(cam.res_x, cam.res_y);
    camera_calculate_w_h(&cam);
    
    render_triangle_to_surface(&cam, &tri1, surf);

    printf("Rendered. Saving...\n");

    SDL_SaveBMP(surf, "out.bmp");
}
