/*
 * =====================================================================================
 *
 *       Filename:  obj.h
 *
 *    Description:  .obj file loader header
 *
 *        Created:  21/03/18 19:20:32
 *       Compiler:  gcc
 *
 *         Author:  Jacob Garby (), thyself@jacobgarby.co.uk
 *
 * =====================================================================================
 */

#ifndef OBJ_H
#define OBJ_H

#define MAX_LINE_LENGTH 128

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/** \brief This struct
 * 
 */
typedef struct {
    vec3d* verts;
    tri3d* tris;
    int amount_verts;
    int amount_tris;
} obj;

int get_amount_lines(FILE* fp);
obj read_OBJ(const char* path);
float* parse_vertex(char*); // Returns pointer to array of exactly three floats (x, y, z)
int* parse_face(char*); // Returns pointer to array of exactly nine integers

#endif
