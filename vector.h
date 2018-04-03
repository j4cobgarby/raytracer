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

#include "material.h"

/** \brief A 3D vector of floats. Internally, just three floats; pretty straightforward.
 */
typedef struct {
    float x; /// The x component of the vector.
    float y; /// The y component of the vector.
    float z; /// The z component of the vector.
} vec3d;

/** \brief A triangle primitive, including a material.
 */
typedef struct {
    vec3d p0; /// One vertex of the triangle.
    vec3d p1; /// One vertex of the triangle.
    vec3d p2; /// One vertex of the triangle.

    vec3d t0; /// The UV coordinate of vertex 0
    vec3d t1; /// The UV coordinate of vertex 1
    vec3d t2; /// The UV coordinate of vertex 2

    vec3d n0; /// The normal at vertex 0
    vec3d n1; /// The normal at vertex 1
    vec3d n2; /// The normal at vertex 2

    material mat; /// The material of the triangle
} tri3d;

/** \brief Calculate a direction vector from two angles (pitch and yaw).
 *  
 *  The direction described by the pitch and yaw is calculated and returned. Simple
 *  as that. Also, if `out` is not-NULL, the resultant vector is copied into it. This
 *  can be useful sometimes. If you don't want to do that, however, just set `out` to
 *  NULL.
 *
 *  \param pitch The pitch angle in degrees.
 *  \param yaw The yaw angle in degrees.
 *  \param out Output vector. If you don't need this, set it to NULL.
 *
 *  \return The direction vector described by pitch and yaw.
 */
vec3d vec3d_from_pitch_yaw(float pitch, float yaw, vec3d* out);

/** \brief Adds two vectors.
 * 
 *  Adds `a` to `b`, and puts the result in `out`, if it's not NULL. Whether it's NULL
 *  or not, the result is also returned.
 *
 *  \param a Vector a.
 *  \param b Vector b.
 *  \param out Output vector.
 *
 *  \return `a` + `b`.
 */
vec3d vec3d_add(vec3d a, vec3d b, vec3d* out);

/** \brief Subtracts vector b from vector a.
 * 
 *  Calculates `a` - `b`, and puts the result in `out`, if it's not NULL. Whether it's NULL
 *  or not, the result is also returned.
 *
 *  \param a Vector a.
 *  \param b Vector b.
 *  \param out Output vector.
 *
 *  \return `a` - `b`.
 */
vec3d vec3d_sub(vec3d a, vec3d b, vec3d* out);

/** \brief Crosses u and v.
 * 
 *  Calculates `u` X `v`, and puts the result in `out`, if it's not NULL. Whether it's NULL
 *  or not, the result is also returned.
 *
 *  \param u Vector u.
 *  \param v Vector v.
 *  \param out Output vector.
 *
 *  \return `u` X `v`.
 */
vec3d vec3d_cross(vec3d u, vec3d v, vec3d* out);

/** \brief Scales a vector by a scalar.
 * 
 *  Calculates `u` * `s`, and puts the result in `out`, if it's not NULL. Whether it's NULL
 *  or not, the result is also returned.
 *
 *  \param u Vector u.
 *  \param s The scalar.
 *  \param out Output vector.
 *
 *  \return `u` * `s`.
 */
vec3d vec3d_scale(vec3d u, float s, vec3d* out);

/** \brief Gets the dot product of two vectors.
 * 
 *  Calculates the dot product of `u` and `v`, and puts the result in `out` if `out` is not NULL.
 *  The result is always returned.
 *
 *  \param u Vector u
 *  \param v Vector v
 *  \param out Output vector
 *
 *  \return dot product of `u` and `v`.
 */
float vec3d_dot(vec3d u, vec3d v, float* out);

/** \brief Nicely prints out a 3D vector.
 *  
 *  Enough said.
 *
 *  \param v The vector to print.
 */
void vec3d_print(vec3d v);

/** \brief Nicely prints out the 3 vertices of a triangle.
 * 
 *  Enough said.
 *
 *  \param t The triangle to print.
 */
void tri3d_print(tri3d t);

/** \brief Calculates the center of a triangle.
 *  
 *  There are many ways to calculate the center of a triangle. This is -- as far as I know --
 *  the least computationally expensive. For each axis, it gets the average on that axis of
 *  all the vertices. For example, the x ordinate of the result is:
 *
 *  \code
 *  center = (v0.x + v1.x + v2.x) / 3.0
 *  \endcode
 *
 *  \param t A pointer to the triangle
 *  \param out A pointer to where you want the center to be stored. NULL, if you don't.
 *
 *  \return The center.
 */
vec3d tri3d_center(tri3d* t, vec3d* out);

/** \brief Normalises `v` in-place.
 * 
 *  Divides the components of `v` by its length, making it a unit vector but
 *  maintaining the direction.
 *
 *  \param v A pointer to the vector to normalise.
 */
void vec3d_norm(vec3d* v);

/** \brief Calculates the squared distance between two positions.
 * 
 *  Uses Pythagoras' theorem, but without the final square root, to calculate the squared
 *  distance between two 3D points. The reason for not square-rooting is that this would be
 *  a lot more computationally expensive, and in a lot of cases you only need distances to
 *  compare them. If you want the _exact_ distance, use vec3d_distsquared.
 *
 *  \param a Vector A
 *  \param b Vector B
 *  \param out Output vector, set to NULL if you don't want this.
 *
 *  \return The result.
 */
float vec3d_distsquared(vec3d a, vec3d b, float* out);

/** \brief Calculates the _exact_ distance between two positions.
 * 
 *  Unlike vec3d_distsquared, this function returns the _exact_ distance between two position vectors,
 *  instead the squared distance. Only use this when you need the actual distance for something, because
 *  in most cases it's unnecessary.
 *
 *  \param a Vector A
 *  \param b Vector B
 *  \param out Output vector, where the distance is stored. Set to NULL if you don't want this.
 *
 *  \return The distance.
 */
float vec3d_dist(vec3d a, vec3d b, float* out);

/** \brief Calculates the length of a vector.
 * 
 *  Enough said.
 *
 *  \param a The vector
 *  \param out I'm tired of writing documentation, I want to go to bed.
 *
 *  \return me to sleep please.
 */
float vec3d_magnitude(vec3d a, float* out);

/** \brief Calculates the angle between two vectors.
 * 
 *  Calculates the angle between two direction vectors in degrees. The vectors DON'T
 *  have to be normalised.
 *
 *  \param a Vector A
 *  \param b Vector b
 *  \param out A pointer where the angle is stored. Set to NULL if you don't want this.
 *
 *  \return The angle.
 */
float vec3d_angle(vec3d a, vec3d b, float* out);

#endif
