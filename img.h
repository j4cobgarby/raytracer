/*
 * =====================================================================================
 *
 *       Filename:  img.h
 *
 *    Description:  Image writing with SDL
 *
 *        Created:  17/03/18 13:29:40
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#ifndef IMG_H
#define IMG_H

#include <stdlib.h>
#include <SDL2/SDL.h>

void put_pixel(SDL_Surface* surf, int x, int y, Uint32 pixel);
SDL_Surface* create_surface(int width, int height);

#endif
