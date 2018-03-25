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

/*
int main() {
    SDL_Surface* surf;
    scene sc;

    camera cam = {
        .origin = (vec3d){0,0,0},
        .yaw    = 0,
        .pitch  = 0,
        .fov    = 85,
        // ..leave w and h undefined for now
        .res_x  = 1080,
        .res_y  = 720
    };

    sc.tris = malloc(sizeof(tri3d) * 3);
    sc.amount_tris = 3;

    sc.tris[0] = (tri3d) {
       (vec3d){2.5, 0.2, 0},
       (vec3d){1.5, -0.3, -0.5},
       (vec3d){1.5, -0.2, 0.5},

       (material){.diffuse = 0x00ff00ff}
    };
    sc.tris[1] = (tri3d) {
        (vec3d){3.0, 1.5, 1.5},
        (vec3d){3.0, 0.5, 1.0},
        (vec3d){2.5, 0.7, 2.0},

        (material){.diffuse = 0xff0000ff}
    };

    sc.tris[2] = (tri3d) {
        (vec3d){2.0, 0.2, -0.1},
        (vec3d){1.8, 0.1, -0.2},
        (vec3d){1.8, 0.1, 0.0},
        
        (material){.diffuse = 0x0000ffff}
    };

    sc.pointlights = malloc(sizeof(point_light) * 1);
    sc.amount_pointlights = 1;
    sc.pointlights[0] = (point_light) {
        (vec3d){2.0, 0.5, 0.05},
        0.8
    };

    sc.cam = cam;
    sc.ambient_intensity = 0.1;

    surf = create_surface(cam.res_x, cam.res_y);
    camera_calculate_w_h(&sc.cam);
    
    render_scene_to_surface(&sc, surf);

    printf("Rendered. Saving...\n");

    SDL_SaveBMP(surf, "out.bmp");
}
*/

int main() {
    SDL_Surface* surf;
    scene sc;
    obj cube;

    cube = read_OBJ("objs/cube.obj");
    
    sc.cam = (camera){
        .origin = (vec3d){-6, 2.5, 2.5},
        .yaw    = 20,
        .pitch  = -18,
        .fov    = 85,
        .res_x  = 1080,
        .res_y  = 720
    };

    sc.amount_tris = cube.amount_tris;
    sc.tris = cube.tris;

    sc.ambient_intensity = 0.2;

    sc.amount_pointlights = 1;
    sc.pointlights = malloc(sizeof(point_light) * sc.amount_pointlights);
    sc.pointlights[0] = (point_light){
        .pos = (vec3d){-2.28037, 2.17283, 0},
        .energy = 1.1
    };

    camera_calculate_w_h(&sc.cam);

    surf = create_surface(sc.cam.res_x, sc.cam.res_y);

    render_scene_to_surface(&sc, surf);

    SDL_SaveBMP(surf, "out.bmp");
}
