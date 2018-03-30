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
#include "obj.h"
#include "scene.h"
#include "thpool.h"

int main(int argc, char** argv) {
    SDL_Surface* surf;
    scene sc;
    obj shape;

    if (argc != 2) {
        printf("Usage: raycaster <.obj file path>\n");
        exit(EXIT_FAILURE);
    }

    shape = read_OBJ(argv[1]);

    sc.cam = (camera){
        .origin = (vec3d){-1.82544, 0.50102, -0.68972},
        .yaw    = -16.8,
        .pitch  = -16.8,
        .fov    = 85,
        .res_x  = 500,
        .res_y  = 500
    };

    sc.amount_tris = shape.amount_tris;
    sc.tris = shape.tris;

    sc.ambient_intensity = 0.2;

    sc.amount_pointlights = 1;
    sc.pointlights = malloc(sizeof(point_light) * sc.amount_pointlights);
    sc.pointlights[0] = (point_light){
        .pos = (vec3d){-1.14685, 1.11385, -1.36285},
        .energy = 1.5
    };

    camera_calculate_w_h(&sc.cam);

    surf = create_surface(sc.cam.res_x, sc.cam.res_y);

    printf("Must lock? [%d]\n", SDL_MUSTLOCK(surf));

    printf("Rendering..");
    fflush(stdout);
    render_scene_to_surface(&sc, surf);
    printf("Done!\n");

    SDL_SaveBMP(surf, "out.bmp");
}
