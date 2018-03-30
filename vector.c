/*
 * =====================================================================================
 *
 *       Filename:  vector.c
 *
 *    Description:  Vector implementation
 *
 *        Created:  17/03/18 13:07:27
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#include "vector.h"

void vec3d_norm(vec3d* vec) {
    float length = sqrtf(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
}

vec3d tri3d_center(tri3d* t, vec3d* out) {
    vec3d result = {
        (1.f/3.f)*(t->p0.x + t->p1.x + t->p2.x),
        (1.f/3.f)*(t->p0.y + t->p1.y + t->p2.y),
        (1.f/3.f)*(t->p0.z + t->p1.z + t->p2.z)
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

vec3d vec3d_from_pitch_yaw(float pitch, float yaw, vec3d* out) {
    float xzlen = cos(pitch * (M_PI/180));
    vec3d result = {
        xzlen * cos(yaw * (M_PI/180)),
        sin(pitch * (M_PI/180)),
        xzlen * sin(-yaw * (M_PI/180))
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

vec3d vec3d_add(vec3d a, vec3d b, vec3d* out) {
    vec3d result = {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

vec3d vec3d_sub(vec3d a, vec3d b, vec3d* out) {
    vec3d result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

vec3d vec3d_cross(vec3d u, vec3d v, vec3d* out) {
    vec3d result = {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

vec3d vec3d_scale(vec3d u, float s, vec3d* out) {
    vec3d result = {
        u.x * s,
        u.y * s,
        u.z * s
    };

    if (out != NULL) {
        memcpy(out, &result, sizeof(vec3d));
    }

    return result;
}

float vec3d_distsquared(vec3d a, vec3d b, float* out) {
    vec3d between = vec3d_sub(a, b, NULL);
    float distsquared = between.x*between.x + between.y*between.y + between.z*between.z;

    if (out != NULL) {
        *out = distsquared;
    }

    return distsquared;
}

float vec3d_dist(vec3d a, vec3d b, float* out) {
    float dist = sqrt(vec3d_distsquared(a, b, NULL));

    if (out != NULL) {
        *out = dist;
    }

    return dist;
}

float vec3d_dot(vec3d u, vec3d v, float* out) {
    float result = 0;
    result += u.x * v.x;
    result += u.y * v.y;
    result += u.z * v.z;

    if (out != NULL) {
        *out = result;
    }

    return result;
}

void vec3d_print(vec3d v) {
    printf("->\n\t{%f, %f, %f}\n", v.x, v.y, v.z);
}

void tri3d_print(tri3d t) {
    printf("|>\n\t{\n\t\t{%f,%f,%f},\n\t\t{%f,%f,%f},\n\t\t{%f,%f,%f}\n\t}\n",
            t.p0.x, t.p0.y, t.p0.z,
            t.p1.x, t.p1.y, t.p1.z,
            t.p2.x, t.p2.y, t.p2.z);
}

float vec3d_magnitude(vec3d a, float* out) {
    float result = sqrtf(a.x*a.x+a.y*a.y+a.z*a.z);

    if (out != NULL) {
        *out = result;
    }

    return result;
}

float vec3d_angle(vec3d a, vec3d b, float* out) {
    float costheta = (vec3d_dot(a, b, NULL))/(vec3d_magnitude(a, NULL)*vec3d_magnitude(b, NULL));
    float theta  = acosf(costheta) * (180.0f/M_PI);

    if (out != NULL) {
        *out = theta;
    }

    return theta;
}
