/*
 * =====================================================================================
 *
 *       Filename:  material.h
 *
 *    Description:  Material properties of triangles (colour, etc.)
 *
 *        Created:  20/03/18 16:44:20
 *       Compiler:  gcc
 *
 *         Author:  Jacob 
 *
 * =====================================================================================
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/** \brief A struct with information about the material of a triangle or mesh.
 */
typedef struct {
    Uint32 diffuse; /// The diffuse colour of the material. Basically, the 'base' colour.
    Uint32 specular; /// The specular colour of the material.
    float reflectivity; /// How reflective the material is, from 0-1, where 1 is totally reflective and 0 is not at all.
    float transparency; /// How transparent the material is, from 0-1, where 1 is totally opaque.
    SDL_Surface* texture; /// The texture 
} material;

#endif
