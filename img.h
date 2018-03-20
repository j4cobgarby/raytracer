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

/** \brief Plots a pixel of a specific colour at a specific place on a specific surface.
 * 
 *  Quite useful for making images, this function plots a pixel of colour `pixel` on the
 *  surface specified by `surf`, at (x, y), where (0, 0) is the top-left. It even works
 *  with different colour depths!
 *
 *  \param surf A pointer to an SDL surface, which the pixel is plotted on.
 *  \param x The x-position of the pixel, starting at 0 = leftmost.
 *  \param y The y-position of the pixel, starting at 0 = upmost.
 *  \param pixel The colour of the pixel.
 */
void put_pixel(SDL_Surface* surf, int x, int y, Uint32 pixel);


/** \brief Convenient way to create an SDL surface of a given width and height.
 *
 *  I think it should be fairly self explanatory, to be honest.
 *
 *  \param width How wide the surface is, in pixels.
 *  \param height How tall the surface is, in pixels.
 *
 *  \return A pointer to an SDL Surface, which you can then render on.
 */
SDL_Surface* create_surface(int width, int height);

#endif
