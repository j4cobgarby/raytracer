/*
 * =====================================================================================
 *
 *       Filename:  intersections.h
 *
 *    Description:  Declarations of some functions for checking intersections, etc.
 *
 *        Version:  1.0
 *        Created:  17/03/18 13:01:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob 
 *
 * =====================================================================================
 */

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "vector.h"

int ray_intersect_tri(vec3d ray_origin, vec3d ray_vector, tri3d* triangle, vec3d* point_of_intersection); 

#endif
