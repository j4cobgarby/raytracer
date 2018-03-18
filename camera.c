/*
 * =====================================================================================
 *
 *       Filename:  camera.c
 *
 *    Description:  Camera implementation
 *
 *        Version:  1.0
 *        Created:  18/03/18 13:27:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */
#include "camera.h"

void camera_calculate_w_h(camera* cam) {
    cam->w = 2 * tan((cam->fov/2) * M_PI/180);
    cam->h = ((float)cam->res_y/(float)cam->res_x)*cam->w;
}

float camera_calculate_ray_yaw(camera* cam, unsigned int pixel_x) {
    return cam->yaw + atan((cam->w/2 - (float)pixel_x*(cam->w/(float)cam->res_x)) * M_PI/180);
}

float camera_calculate_ray_pitch(camera* cam, unsigned int pixel_y) {
    return cam->pitch + atan((cam->h/2 - (float)pixel_y*(cam->h/(float)cam->res_y)) * M_PI/180);
}

