/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Raycaster main
 *
 *        Version:  1.0
 *        Created:  17/03/18 00:30:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */
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

int main(int argc, char** argv) {
    vec3d origin = {0,0,0}, ray_vector = {1,0,0};
    tri3d triangle;
    triangle.p0 = (vec3d){1.22501,  -1, 1.5};
    triangle.p1 = (vec3d){3,  -1,  -1};
    triangle.p2 = (vec3d){3, 1.5,  -1};

    tri3d_print(triangle);

    vec3d out;

    if (ray_intersect_tri(origin, ray_vector, &triangle, &out)) {
        printf("Hit at position:\n");
        vec3d_print(out);
    }

    return 0;
}
