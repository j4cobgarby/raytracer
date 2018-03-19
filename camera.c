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
    float result = (pixel_x < cam->res_x/2 ? -1 : 1) * atan(fabs(
                    (cam->w * (float)pixel_x)/((float)cam->res_x) - ((cam->w)/2.0)
                    )) * 180.0/M_PI;

    return result + cam->yaw;
}

float camera_calculate_ray_pitch(camera* cam, unsigned int pixel_y) {
    float result = (pixel_y < cam->res_y/2 ? -1 : 1) * atan(fabs(
                    (cam->h * (float)pixel_y)/((float)cam->res_y) - ((cam->h)/2.0)
                    )) * 180.0/M_PI;

    return result + cam->pitch;
}
