/*
 * =====================================================================================
 *
 *       Filename:  vector.h
 *
 *    Description:  Vector header file
 *
 *        Version:  1.0
 *        Created:  17/03/18 13:02:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3d;

typedef struct {
    vec3d p0;
    vec3d p1;
    vec3d p2;
} tri3d;

vec3d vec3d_from_pitch_yaw(float pitch, float yaw, vec3d* out);
vec3d vec3d_add(vec3d a, vec3d b, vec3d* out);
vec3d vec3d_sub(vec3d a, vec3d b, vec3d* out);
vec3d vec3d_cross(vec3d u, vec3d v, vec3d* out);
vec3d vec3d_scale(vec3d u, float s, vec3d* out);
float vec3d_dot(vec3d u, vec3d v, float* out);
void vec3d_print(vec3d v);
void tri3d_print(tri3d t);


#endif
