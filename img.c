/*
 * =====================================================================================
 *
 *       Filename:  img.c
 *
 *    Description:  implementation of img.h
 *
 *        Version:  1.0
 *        Created:  17/03/18 13:29:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#include "img.h"

void set_pixel(SDL_Surface* surf, int x, int y, Uint32 pix) {
    Uint32* target = (Uint32*) surf->pixels + y * surf->pitch + 
        x * sizeof(*target);
    *target = pix;
}

SDL_Surface* create_surface(int width, int height) {
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 32, 
            rmask, gmask, bmask, amask);
    return surf;
}
