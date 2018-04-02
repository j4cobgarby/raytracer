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

    for (int i = 0; i < sc->amount_pointlights; i++) {
        if (can_see_specific_light(sc, check_point, ignore_index, i)) return 1; 
    }

    return 0;
}

float calculate_light_intensity(scene* sc, vec3d check_point, int ignore_index) {
    float intensity;
    float distance_squared;
    float angle_to_light;

    intensity = sc->ambient_intensity;

    if (!can_see_light(sc, check_point, ignore_index)) return 0;

    for (int i = 0; i < sc->amount_pointlights; i++) {
        // Use the inverse square law to calculate the actual intensity
        vec3d_distsquared(check_point, sc->pointlights[i].pos, &distance_squared);
        angle_to_light = vec3d_angle(
                calc_face_normal(sc->tris[ignore_index].p0, sc->tris[ignore_index].p1, sc->tris[ignore_index].p2,
                                            sc->tris[ignore_index].n0, sc->tris[ignore_index].n1, sc->tris[ignore_index].n2
                                             ), 
                vec3d_sub(sc->pointlights[i].pos, tri3d_center(&sc->tris[ignore_index], NULL), NULL), 
                NULL);
        intensity += (sc->pointlights[i].energy / distance_squared) * (90.0f-angle_to_light)/90.0f; 
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

inline void render_scene_at_xy(scene* sc, SDL_Surface* surf, float** zbuff, int x, int y) {
    int closest_triangle_index = -1;

    float ray_pitch = camera_calculate_ray_pitch(&sc->cam, y);
    float ray_yaw   = camera_calculate_ray_yaw(&sc->cam, x);
    float distance_squared;

    vec3d ray_direction = vec3d_from_pitch_yaw(ray_pitch, ray_yaw, NULL);
    vec3d poi;
    vec3d closest_poi;

    Uint32 pix_colour = sc->background_colour;

    for (int i = 0; i < sc->amount_tris; i++) {
        if (ray_intersect_tri(sc->cam.origin, ray_direction, &sc->tris[i], &poi)) {
            if (vec3d_distsquared(sc->cam.origin, poi, &distance_squared) < zbuff[x][y]) {
                zbuff[x][y] = distance_squared;
                closest_triangle_index = i;
                closest_poi = poi;
            }
        }
    }

    if (closest_triangle_index > 0) {
        // hit a triangle, this is the closest, so render it!

        pix_colour = sc->tris[closest_triangle_index].mat.diffuse;

        if (can_see_light(sc, closest_poi, closest_triangle_index)) {
            pix_colour = multiply_colour(pix_colour, calculate_light_intensity(sc, closest_poi, closest_triangle_index));
        } else {
            pix_colour = multiply_colour(pix_colour, sc->ambient_intensity);
        }
    }

    SDL_LockSurface(surf);
    put_pixel(surf, x, y, pix_colour);
    SDL_UnlockSurface(surf);
}

void render_scene_at_xy_thread(void* args) {
    render_args* rargs = (render_args*)args;
    render_scene_at_xy(rargs->sc, rargs->surf, rargs->zbuff, rargs->x, rargs->y);
    *(rargs->pixels_rendered)++;
}

void render_scene_to_surface(scene* sc, SDL_Surface* surf) {
    float** zbuff = malloc(sizeof(float*) * sc->cam.res_x);
    render_args*** args_array;
    threadpool thpool = thpool_init(4); // make 8 threads
    int pixels_rendered;

    for (size_t i = 0; i < sc->cam.res_x; i++) {
        zbuff[i] = malloc(sizeof(float) * sc->cam.res_y);
        for (size_t j = 0; j < sc->cam.res_y; j++) {
            zbuff[i][j] = INFINITY;
        }
    }

    args_array = malloc(sizeof(render_args**) * sc->cam.res_y);
    for (size_t y = 0; y < sc->cam.res_y; y++) {
        args_array[y] = malloc(sizeof(render_args*) * sc->cam.res_x);
        for (size_t x = 0; x < sc->cam.res_x; x++) {
            args_array[y][x] = malloc(sizeof(render_args));
            args_array[y][x]->sc = sc;
            args_array[y][x]->surf = surf;
            args_array[y][x]->x = x;
            args_array[y][x]->y = y;
            args_array[y][x]->zbuff = zbuff;
            args_array[y][x]->pixels_rendered = &pixels_rendered;
        }
    }

    printf("Arguments allocated...\n");

    for (size_t y = 0; y < sc->cam.res_y; y++) {
        for (size_t x = 0; x < sc->cam.res_x; x++) {
            thpool_add_work(thpool, (void*)render_scene_at_xy_thread, (void*)args_array[y][x]);
        }
    }

    thpool_wait(thpool);
    printf("Done rendering.\n");
    thpool_destroy(thpool);
    printf("Destroyed threadpool\n");
    
    for (size_t i = 0; i < sc->cam.res_x; i++) {
        free(zbuff[i]);
    }
    free(zbuff);
    printf("Destroyed Z-Buffer\n");
    
    for (size_t y = 0; y < sc->cam.res_y; y++) {
        for (size_t x = 0; x < sc->cam.res_x; x++) {
            free(args_array[y][x]);
        }
        free(args_array[y]);
    }
    free(args_array);
    printf("Destroyed argument array\n");
}
