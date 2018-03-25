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

int can_see_specific_light(scene* sc, vec3d check_point, int ignore_index, int light_index) {
    vec3d ray_direction;
    vec3d hitpoint;

    vec3d_sub(sc->pointlights[light_index].pos, check_point, &ray_direction);
    for (int j = 0; j < sc->amount_tris; j++) {
        if (j != ignore_index) {
            if (ray_intersect_tri(check_point, ray_direction, &sc->tris[j], &hitpoint)) {
                if (vec3d_distsquared(check_point, hitpoint, NULL) <= 
                            vec3d_distsquared(check_point, sc->pointlights[light_index].pos, NULL)) return 0;
            }
        } 
    }

    return 1;
}

int can_see_light(scene* sc, vec3d check_point, int ignore_index) {
    vec3d ray_direction;
    vec3d hitpoint;

    for (int i = 0; i < sc->amount_pointlights; i++) {
        if (can_see_specific_light(sc, check_point, ignore_index, i)) return 1; 
    }

    return 0;
}

float calculate_light_intensity(scene* sc, vec3d check_point, int ignore_index) {
    float intensity;
    float distance_squared;

    intensity = sc->ambient_intensity;

    if (!can_see_light(sc, check_point, ignore_index)) return 0;

    for (int i = 0; i < sc->amount_pointlights; i++) {
        // Use the inverse square law to calculate the actual intensity
        vec3d_distsquared(check_point, sc->pointlights[i].pos, &distance_squared);
        intensity += sc->pointlights[i].energy / distance_squared; 
    }

    return intensity;
}

Uint32 multiply_colour(Uint32 colour, float scalar) {
    int r,g,b,a;
    Uint32 result;

    r = colour >> 24;
    g = (colour >> 16) & 0xff;
    b = (colour >> 8) & 0xff;
    a = colour & 0xff;

    r = (r*scalar>0xff?0xff:r*scalar);
    g = (g*scalar>0xff?0xff:g*scalar);
    b = (b*scalar>0xff?0xff:b*scalar);

    result = (Uint32)(r<<24)+(g<<16)+(b<<8)+a;

    return result;
}

void render_triangle_to_surface(scene* sc, int triangle_index, SDL_Surface* surf, float** zbuff) {
    float ray_pitch, ray_yaw;
    Uint32 pixel_colour;
    vec3d ray_vector;
    vec3d poi; // point of intersection
    tri3d* triangle;
    camera* cam;
    float distance_squared;

    triangle = &(sc->tris[triangle_index]);
    cam = &(sc->cam);

    SDL_LockSurface(surf);

    for (unsigned int y = 0; y < cam->res_y; y++) {
        for (unsigned int x = 0; x < cam->res_x; x++) {
            ray_pitch = camera_calculate_ray_pitch(cam, y);
            ray_yaw = camera_calculate_ray_yaw(cam, x);
            vec3d_from_pitch_yaw(ray_pitch, ray_yaw, &ray_vector);
            pixel_colour = 0x000000ff;

            if (ray_intersect_tri(cam->origin, ray_vector, triangle, &poi)) {
                vec3d_distsquared(cam->origin, poi, &distance_squared);
                if (distance_squared > zbuff[x][y]) {
                    continue;
                }
                zbuff[x][y] = distance_squared;

                pixel_colour = triangle->mat.diffuse;

                if (can_see_light(sc, poi, triangle_index)) {
                    pixel_colour = multiply_colour(pixel_colour, calculate_light_intensity(sc, poi, triangle_index));
                } else {
                    pixel_colour = multiply_colour(pixel_colour, sc->ambient_intensity);
                }

                put_pixel(surf, x, y, pixel_colour);
            }
        }
    }

    SDL_UnlockSurface(surf);
}

void render_scene_to_surface(scene* sc, SDL_Surface* surf) {
    float** zbuff = malloc(sizeof(float*) * sc->cam.res_x);
    for (int i = 0; i < sc->cam.res_x; i++) {
        zbuff[i] = malloc(sizeof(float) * sc->cam.res_y);
        for (int j = 0; j < sc->cam.res_y; j++) {
            zbuff[i][j] = INFINITY;
        }
    }

    for (int i = 0; i < sc->amount_tris; i++) {
        render_triangle_to_surface(sc, i, surf, zbuff);
    }
}
