/*
 * =====================================================================================
 *
 *       Filename:  intersections.h
 *
 *    Description:  Declarations of some functions for checking intersections, etc.
 *
 *        Created:  17/03/18 13:01:24
 *       Compiler:  gcc
 *
 *         Author:  Jacob 
 *
 * =====================================================================================
 */

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "vector.h"

/** \brief Calculate if and where a ray intersects a triangle.
 *  
 *  This is implemented using the Mӧller-Trumbore algorithm, but only because it looked the most sane
 *  to me. I honestly don't know how it works, but it does! I've tested it (I had doubts about my
 *  implementation, not the algorithm itself.)
 *  It returns 1 if the ray did hit, otherwise 0. If it hits, the global position of intersection is
 *  copied into `point_of_intersection`.
 *
 *  \param ray_origin The position from which the ray is projected.
 *  \param ray_vector The direction vector of the ray. This should be normalised by you.
 *  \param triangle The triangle which you're checking.
 *  \param point_of_intersection The vector where the position of the intersection is put.
 *
 *  \return 1 if there's an intersection, else 0.
 */
inline int ray_intersect_tri(vec3d ray_origin, vec3d ray_vector, tri3d* triangle, vec3d* point_of_intersection); 

#endif
