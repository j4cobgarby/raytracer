/*
 * =====================================================================================
 *
 *       Filename:  light.h
 *
 *    Description:  Lights header
 *
 *        Created:  24/03/18 11:48:38
 *       Compiler:  gcc
 *
 *         Author:  Jacob Garby (), thyself@jacobgarby.co.uk
 *
 * =====================================================================================
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

/*  \brief A point light is a type of light which emits light equally in all directions from
 *  its position.
 */
typedef struct {
    vec3d pos; /// The position of the point light
    float energy; /// The energy of the light, where intensity of a point = energy/distance^2
} point_light;

#endif
