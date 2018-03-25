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

typedef struct {
    tri3d* tris;
    point_light* pointlights;
    camera cam;
    int amount_tris, amount_pointlights;
    float ambient_intensity;
} scene;

#endif
