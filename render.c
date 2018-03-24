/*
 * =====================================================================================
 *
 *       Filename:  render.c
 *
 *    Description:  render implementation
 *
 *        Created:  20/03/18 08:03:21
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */
#include "render.h"

int can_see_light(scene* sc, vec3d check_point, int ignore_index) {
    vec3d ray_direction;
    vec3d hitpoint;

    for (int i = 0; i < sc->amount_pointlights; i++) {
        vec3d_sub(sc->pointlights[i].pos, check_point, &ray_direction);
        for (int j = 0; j < sc->amount_tris; j++) {
            if (j != ignore_index) {
               if (ray_intersect_tri(check_point, ray_direction, &sc->tris[j], &hitpoint)) return 0;
            }      
        }
    }

    return 1;
}

void render_triangle_to_surface(scene* sc, int triangle_index, SDL_Surface* surf) {
    float ray_pitch, ray_yaw;
    Uint32 pixel_colour;
    vec3d ray_vector;
    vec3d poi; // point of intersection
    tri3d* triangle;
    camera* cam;

    triangle = &(sc->tris[triangle_index]);
    cam = &(sc->cam);

    tri3d_print(*triangle);

    SDL_LockSurface(surf);

    for (unsigned int y = 0; y < cam->res_y; y++) {
        for (unsigned int x = 0; x < cam->res_x; x++) {
            ray_pitch = camera_calculate_ray_pitch(cam, y);
            ray_yaw = camera_calculate_ray_yaw(cam, x);
            vec3d_from_pitch_yaw(ray_pitch, ray_yaw, &ray_vector);
            pixel_colour = 0x000000ff;

            if (ray_intersect_tri(cam->origin, ray_vector, triangle, &poi)) {
                pixel_colour = triangle->mat.diffuse;

                if (!can_see_light(sc, poi, triangle_index)) {
                    pixel_colour = 0x000000ff;
                }

                put_pixel(surf, x, y, pixel_colour);
            }
        }
    }

    SDL_UnlockSurface(surf);
}

void render_scene_to_surface(scene* sc, SDL_Surface* surf) {
    for (int i = 0; i < sc->amount_tris; i++) {
        render_triangle_to_surface(sc, i, surf);
    }
}
