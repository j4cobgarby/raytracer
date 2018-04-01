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

/** \brief This struct represents an .obj file.
 * 
 *  Here's how to generate an instance of this struct from an .obj file:
 *
 *  \code
 *  obj my_object = read_OBJ("suzanne.obj");
 *  \endcode
 *
 *  Which parses the file `suzanne.obj` into the struct.
 */
typedef struct {
    vec3d* verts; /// Array of the vertices in the object.
    vec3d* norms; /// Array of vertex normals in the object.
    tri3d* tris; /// Array of triangles in the object.
    int amount_verts; /// Amount of vertices.
    int amount_tris; /// Amount of triangles.
    int amount_norms; /// Amount of vertex normals.
} obj;

/** \brief Returns the amount of lines in a the file pointed to by fp.
 *
 *  \param fp A `FILE*` type, referencing the file.
 *
 *  \return An integer representing the amount of lines in the file.
 */
int get_amount_lines(FILE* fp);

/** \brief Read an .obj file, and return the created obj type instance.
 *
 *  This function calls on `parse_vertex`, `parse_normal`, and `parse_face`, to parse
 *  an .obj file. A face definition in an .obj file looks something like this:
 *
 *  \code
 *  f v0/t0/n0 v1/t1/n1 v2/t2/n2
 *  \endcode
 *
 *  ... assuming that the face is a triangle. It's definitely worth noting that this function
 *  can only read object files where every face is a triangle, otherwise it'll carry on and not
 *  break, but disregard the last vertex of that face.
 *
 *  \param path The file path to the .obj
 *
 *  \return A fully initialised obj struct instance.
 */
obj read_OBJ(const char* path);

/** \brief Parses a vertex line in an .obj file to an array of floats
 * 
 *  A vertex definition looks like this:
 *
 *  \code
 *  v x y z
 *  \endcode
 *
 *  ... where x, y, and z are the coordinates of the point.
 *
 *  \param s The string which is a line of the file representing a vertex.
 *
 *  \return Exactly three floats, representing x, y, and z
 */
float* parse_vertex(char*);

/** \brief Parses a normal in an .obj file to an array of floats
 * 
 *  \code
 *  vn x y z
 *  \endcode
 *
 *  Normals are stored in the file almost identically to the vertices, except for
 *  the 'n' after the 'v'.
 *
 *  \param s The string in the .obj file representing the normal.
 *
 *  \return Exactly three floats, representing x, y, and z of the normal
 */
float* parse_normal(char*);

/** \brief Parses a face in an .obj file to an array of integers.
 *
 *  Faces are stored like this:
 *
 *  \code
 *  f v0/t0/n0 v1/t1/n1 v2/t2/n2
 *  \endcode
 *
 *  This function simply reads the values, in order, into an array of 9 integers.
 *
 *  \param s The string.
 *
 *  \return The array of 9 integers.
 */
int* parse_face(char*);

/** \brief Calculates a triangle normal from the normals and positions of its three vertices.
 * 
 *  This is useful for working out the angle from a triangle to a light source.
 *
 *  \param v0 Vertex 0
 *  \param v1 Vertex 1
 *  \param v2 Vertex 2
 *  \param n0 Normal 0
 *  \param n1 Normal 1
 *  \param n2 Normal 2
 *
 *  \return The normal of the triangle.
 */
vec3d calc_face_normal(vec3d v0, vec3d v1, vec3d v2, vec3d n0, vec3d n1, vec3d n2);

#endif
