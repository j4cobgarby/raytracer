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
    vec3d* indexed_verts;
    tri3d* tris;
    int amount_verts;
    int amount_tris;
} obj;

obj read_OBJ(const char* path);

#endif
