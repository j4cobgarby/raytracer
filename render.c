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

void render_triangle_to_surface(camera* cam, tri3d* triangle, SDL_Surface* surf) {
    float ray_pitch, ray_yaw;
    vec3d ray_vector;
    vec3d poi; // point of intersection

    SDL_LockSurface(surf);

    for (unsigned int y = 0; y < cam->res_y; y++) {
        for (unsigned int x = 0; x < cam->res_x; x++) {
            ray_pitch = camera_calculate_ray_pitch(cam, y);
            ray_yaw = camera_calculate_ray_yaw(cam, x);
            vec3d_from_pitch_yaw(ray_pitch, ray_yaw, &ray_vector);

            if (ray_intersect_tri(cam->origin, ray_vector, triangle, &poi)) {
                put_pixel(surf, x, y, triangle->mat.diffuse);
            }
        }
    }

    SDL_UnlockSurface(surf);
}

