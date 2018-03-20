/*
 * =====================================================================================
 *
 *       Filename:  camera.h
 *
 *    Description:  header for the camera struct
 *
 *        Created:  18/03/18 12:46:13
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

/** \brief A camera, which renders things.
 * 
 *  Actually, the camera itself doesn't render anything, it just stores the necessary
 *  values needed to work out how to render things.
 *  Think of it as a pyramid. The descriptions of its values will be described as such.
 */
typedef struct {
    vec3d origin; /// The position of the tip of the pyramid.
    float yaw; /// The rotation on the local y-axis.
    float pitch; /// The rotation on the local x-axis. Emphasis on local.
    float fov; /// The angle in degrees at the point of the pyramid, of the x axis.
    float w; /// The physical width of the base of the pyramid. Don't set this manually.
    float h; /// The physical length of the base of the pyramid. Don't set this manually.
    unsigned int res_x; /// The amount of pixels on the x-axis that the camera renders.
    unsigned int res_y; /// The amount of pixels on the y-axis that the camera renders.
} camera;

/** \brief Calculates and sets `w` and `h` of `cam`.
 *
 *  Since you're not meant to set `w` or `h` manually (because it's worked
 *  out based on the values given for the camera), this functions serves to set these
 *  values for you.
 *  Make sure to have initialised all of the other camera values before calling this,
 *  and make sure you've called this BEFORE USING THE CAMERA.
 *
 *  \param cam The camera, of course. A pointer to it.
 */
void camera_calculate_w_h(camera* cam);

/** \brief Calculate the global yaw of a ray from the camera.
 *
 *  Funny story: this function took me a bit over half an hour to think up and implement,
 *  but I was stuck on it for a couple of days. How, you ask? Well, turns out I was testing
 *  it with the wrong values, and _thought_ it wasn't working. Sigh. That's a number of hours
 *  I'm not getting back.
 *  Anyway, you give it the x-index of a pixel (starting at 0, ending at res_x-1), and it'll
 *  give you the required yaw to send a ray to hit it.
 *  Pair this with `camera_calculate_ray_pitch`, and it's pretty useful.
 *
 *  \param cam The camera which the ray will be projected from.
 *  \param pixel_x The x-index of a pixel.
 *
 *  \return The yaw of the ray.
 */
float camera_calculate_ray_yaw(camera* cam, unsigned int pixel_x);

/** \brief Calculate the global pitch of a ray from the camera.
 *
 *  If you've read the description for `camera_calculate_ray_yaw`, you'll know the trouble I went
 *  to to get that one working. Luckily, I had no such problem with this one, because I wrote it
 *  second and just changed some numbers and letters around.
 *  Given the y-index of a pixel (starting at 0, ending at res_y-1), returns the required pitch
 *  to hit it with a ray from the camera origin.
 *  Pair this with `camera_calculate_ray_yaw`, and it's pretty useful.
 *
 *  \param cam The camera which the ray will be projected from.
 *  \param pixel_x The x-index of a pixel.
 *
 *  \return The pitch of the ray.
 */
float camera_calculate_ray_pitch(camera* cam, unsigned int pixel_y);

#endif
