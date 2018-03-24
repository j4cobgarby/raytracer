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

#include <stdlib.h>
#include <SDL2/SDL.h>

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
 */
int can_see_light(scene* sc, vec3d check_point, int ignore_index);

/** \brief Renders a single triangle in three-dimensional space to
 *         a surface.
 *
 *  In practice, this probably won't be used very much, since it only renders
 *  one triangle, and usually you'd want to render a whole mesh. You might think
 *  you can just use this function for every triangle in a mesh, but you shouldn't,
 *  unless you want to take care of rendering order yourself.
 *
 *  \param cam A pointer to the camera to render from.
 *  \param triangle A pointer to the triangle to render, which includes the material.
 *  \param surf The SDL surface pointer to render the triangle to.
 */
void render_triangle_to_surface(scene* sc, int triangle_index, SDL_Surface* surf);

void render_scene_to_surface(scene* sc, SDL_Surface* surf);

#endif
