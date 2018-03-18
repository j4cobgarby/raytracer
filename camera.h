/*
 * =====================================================================================
 *
 *       Filename:  camera.h
 *
 *    Description:  header for the camera struct
 *
 *        Version:  1.0
 *        Created:  18/03/18 12:46:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "intersections.h"
#include "img.h"

/* The camera
 * 
 * origin: a 3d point representing the position of the camera
 * yaw: local y-rotation of the camera
 * pitch: local z-rotation of the camera (assuming x is forwards, locally)
 * fov: the angle of the (not quite a) frustum
 * w: THIS SHOULD BE CALCULATED, NOT MANUALLY SET: the physical width of the camera's focal plane
 * h: ALSO SHOULD BE CALCULATED: the physical height of the camera's focal plane
 * res_x: The amount of pixels horizontally
 * res_y: The amount of pixels vertically
 */
typedef struct {
    vec3d origin;
    float yaw;
    float pitch;
    float fov;
    float w;
    float h;
    unsigned int res_x;
    unsigned int res_y;
} camera;

void camera_calculate_w_h(camera* cam);

float camera_calculate_ray_yaw(camera* cam, unsigned int pixel_x);

float camera_calculate_ray_pitch(camera* cam, unsigned int pixel_y);

#endif
