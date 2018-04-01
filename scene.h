/*
 * =====================================================================================
 *
 *       Filename:  scene.h
 *
 *    Description:  Stores a scene (i.e. objects and lights, and a camera)
 *
 *        Created:  24/03/18 11:56:53
 *       Compiler:  gcc
 *
 *         Author:  Jacob Garby (), thyself@jacobgarby.co.uk
 *
 * =====================================================================================
 */

#ifndef SCENE_H
#define SCENE_H

#include "vector.h"
#include "light.h"
#include "camera.h"

/** \brief Represents a scene which can be rendered
 */
typedef struct {
    tri3d* tris; /// An array of all the triangles in the scene
    point_light* pointlights; /// An array of all the point lights in the scene
    camera cam; /// The camera which the scene is rendered from
    int amount_tris, /// The amount of triangles in `tris`
        amount_pointlights; /// The amount of pointlights in `pointlights`
    float ambient_intensity; /// The ambient intensity of the scene
} scene;

#endif
