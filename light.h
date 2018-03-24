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

typedef struct {
    vec3d pos;
} point_light;

#endif
