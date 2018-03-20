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

/** \brief A struct with information about the material of a triangle or mesh.
 */
typedef struct {
    Uint32 diffuse; /// The diffuse colour of the material. Basically, the 'base' colour.
} material;

#endif
