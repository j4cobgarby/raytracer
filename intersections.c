/*
 * =====================================================================================
 *
 *       Filename:  intersections.c
 *
 *    Description:  Implementation of intersections.h
 *
 *        Version:  1.0
 *        Created:  17/03/18 13:14:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#include "intersections.h"

/*
 * Möller-Trumbore intersection algo
 */
int ray_intersect_tri(vec3d ray_origin, vec3d ray_vector, tri3d* triangle, vec3d* point_of_intersection) {
    const float EPSILON = 0.0000001;
    vec3d edge_1, edge_2, h, s, q;
    float a, f, u, v, t;

    vec3d_sub(triangle->p1, triangle->p0, &edge_1);
    vec3d_sub(triangle->p2, triangle->p0, &edge_2);

    vec3d_cross(ray_vector, edge_2, &h);
    vec3d_dot(edge_1, h, &a);

    if (a > -EPSILON && a < EPSILON) return 0;
    
    f = 1/a;
    vec3d_sub(ray_origin, triangle->p0, &s);
    u = f * vec3d_dot(s, h, NULL);

    if (u < 0.0 || u > 1.0) return 0;

    vec3d_cross(s, edge_1, &q);
    v = f * vec3d_dot(ray_vector, q, NULL);

    if (v < 0.0 || u + v > 1.0) return 0;

    // Now work out t to find out where the intersection point is on the line

    t = f * vec3d_dot(edge_2, q, NULL);

    if (t > EPSILON) {
        vec3d_scale(ray_vector, t, point_of_intersection);
        vec3d_add(*point_of_intersection, ray_origin, point_of_intersection);
        return 1;
    } else {
        return 0; // line intersection, but no ray intersection
    }
}

