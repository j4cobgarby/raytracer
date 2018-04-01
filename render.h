/*
 * =====================================================================================
 *
 *       Filename:  render.h
 *
 *    Description:  Render header
 *
 *        Created:  19/03/18 19:00:41
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#ifndef RENDER_H
#define RENDER_H

#include "img.h"
#include "vector.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "thpool.h"
#include "obj.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

/**  \brief Since the scene is rendered using a thread pool, and a POSIX thread can only take one
 * argument (other than the function), that is a void pointer, a workaround to pass multiple
 * arguments is to wrap them up in a specially designed struct, then cast it to a void pointer,
 * pass it to the function, and then cast it back to a struct pointer.
 */
typedef struct {
    scene* sc; /// The scene to render
    SDL_Surface* surf; /// The surface to render to
    float** zbuff; /// The zbuffer
    int x; /// The x screen-coord to render
    int y; /// The y screen-coord to render

    int* pixels_rendered; /// This is incremented when a pixel is rendered, for the loading bar.
} render_args;

/** \brief Checks if a any light in a scene is illuminating a point.
 *  
 *  For rendering shadows, the following algorithm is applied:
 *
 *      1 : When a ray hits a triangle, a new ray is cast from the point of intersection
 *          to each light.
 *      
 *      2 : If the new ray intersects a triangle on its way to the ray, that means light
 *          isn't reaching it. To check this, use the ray_intersect_tri function, and also
 *          compare the distance from the initial point of intersection to the new point
 *          of intersection with the potentially obstructive triangle.
 *
 *      3 : If light isn't reaching a pixel, draw it in black.
 *
 *  To avoid graphical glitchiness on the surface of a triangle (noise-like patterns), the
 *  triangle which the point of intersection is on is ignored when checking for obstruction.
 *
 *  \param sc A pointer to the scene which contains all the lights, and triangles.
 *  \param check_point The point whose illumination you wish to know.
 *  \param ignore_index The index in the scene of the triangle which the point lies on.
 *
 *  \return 1 if can see any light, else 0
 */
int can_see_light(scene* sc, vec3d check_point, int ignore_index);

/** \brief Similar to `can_see_light`, but instead checks if a SPECIFIC light can be seen.
 *
 *  For more details about how this works, and why it's used, refer to the description of
 *  `can_see_light`.
 *
 *  \param sc A pointer to the scene which you're checking.
 *  \param check_point The point on a triangle which you're checking.
 *  \param ignore_index The index of the triangle which the point is on, so it can be ignored.
 *  \param light_index The index of the light which you want to check.
 *
 *  \return 1 if can see light at light_index, else 0
 */
int can_see_specific_light(scene* sc, vec3d check_point, int ignore_index, int light_index);

/** \brief Calculate the light intensity at a specific point on a triangle in a scene.
 * 
 *  This is done first by using the inverse square law to calculate the intensity of light,
 *  and then calculating the angle from the light to the point to the face normal to work out
 *  how much light would likely be reflected into the camera.
 *
 *  This is done for every light in the scene, and then summed, since the intensity is additive.
 *
 *  \param sc A pointer to the scene which everything's in.
 *  \param check_point The point for which the intensity is being calculated.
 *  \param ignore_index The triangle which the point is on.
 *
 *  \return A multiplier for the intensity of light.
 */
float calculate_light_intensity(scene* sc, vec3d check_point, int ignore_index);

/** \brief A simple helper function to multiply a colour by an intensity.
 *
 *  This creates a new colour from:
 *
 *  r = old_r * scalar
 *  g = old_g * scalar
 *  b = old_b * scalar
 *  a = old_a
 *
 *  It wouldn't really make sense to multiply the alpha, since this usually isn't what you want
 *  to do.
 *
 *  \param colour The base colour
 *  \param scalar The intensity
 */
Uint32 multiply_colour(Uint32 colour, float scalar);

/** \brief Renders a scene to a surface at the pixel x, y
 * 
 *  First, this calculates the triangle which is closest to the camera at this pixel.
 *  Then, it renders the triangle at the point where the ray that the camera sends out
 *  intersects the pixel to the pixel x, y on the surface.
 *
 *  \param sc The scene to render
 *  \param surf The surface to render it to. It should be an RGB surface.
 *  \param zbuff The Z-Buffer
 *  \param x The x coordinate on the surface to render to
 *  \param y The y coordinate on the surface to render to
 */
void render_scene_at_xy(scene* sc, SDL_Surface* surf, float** zbuff, int x, int y);

/** \brief Same as `render_scene_at_xy`, but designed for use with a thread
 * 
 *  POSIX threads can only take a single void pointer argument, so this takes an instance
 *  of a pointer to a render_args struct casted to a void pointer, then casts it back to
 *  a pointer to a render_args struct on the receiving end.
 *
 *  \param args A pointer to a render_args struct, cast to a void pointer
 */
void render_scene_at_xy_thread(void* args);

/** \brief Creates a threadpool to render a scene to a surface.
 * 
 *  Essentially what this does is creates a bunch of threads, then tells them each to render
 *  the first few coordinates, and when they've finished that, reassignes them to the next
 *  coordinate that hasn't been rendered. This is a good way of speeding up the rendering
 *  without having to try and code for the GPU.
 *
 *  \param sc The scene to render
 *  \param surf The surface to render to
 */
void render_scene_to_surface(scene* sc, SDL_Surface* surf);

#endif
