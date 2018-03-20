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

#include <stdlib.h>
#include <SDL2/SDL.h>

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
void render_triangle_to_surface(camera* cam, tri3d* triangle, SDL_Surface* surf);

/** \brief Not implemented yet!! Render multiple triangles (a mesh) to the surface.
 *
 *  Generally, you'll programatically generate the array of triangles, but if you want
 *  to manually type out an object, feel free. This uses a Z-buffer to speed up rendering
 *  by only rendering objects which are seen! Handy.
 *
 *  \param cam A pointer to the camera to render from.
 *  \param triangles A pointer to the first pointer to a triangle in an array of `num' triangle pointers.
 *  \param num The amount of triangle pointers.
 *  \param surf The SDL surface pointer to render the triangle to.
 */
void render_triangles_to_surface(camera* cam, tri3d** triangles, int num, SDL_Surface* surf);

#endif
