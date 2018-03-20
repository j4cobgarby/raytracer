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

void render_triangle_to_surface(camera* cam, tri3d* triangle, Uint32 colour, SDL_Surface* surf);

void render_triangles_to_surface(camera* cam, tri3d** triangle, int num, SDL_Surface* surf);

#endif
