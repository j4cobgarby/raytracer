/*
 * =====================================================================================
 *
 *       Filename:  obj.c
 *
 *    Description:  obj loader
 *
 *        Created:  23/03/18 16:57:11
 *       Compiler:  gcc
 *
 *         Author:  Jacob Garby (), thyself@jacobgarby.co.uk
 *
 * =====================================================================================
 */

#include "obj.h"

int get_amount_lines(FILE* fp) {
    int ch, result = 0;
    do {
        ch = fgetc(fp);
        if (ch == '\n') result++;
    } while (ch != EOF);
    return result;
}

vec3d calc_face_normal(vec3d v0, vec3d v1, vec3d v2, vec3d n0, vec3d n1, vec3d n2) {
    vec3d p0, p1, face_normal, vert_normal;
    float dot_prod;

    vec3d_sub(v1, v0, &p0);
    vec3d_sub(v2, v0, &p1);
    vec3d_cross(p0, p1, &face_normal);

    vert_normal = n0;
    vec3d_dot(face_normal, vert_normal, &dot_prod);

    return (dot_prod < 0.f) ? vec3d_scale(face_normal, -1.f, NULL) : face_normal;
}

obj read_OBJ(const char* path) {
    FILE* fp;

    size_t amount_file_lines = 0;
    size_t amount_vertices = 0; // The amount of vertices in the object. Indices to these are started at 1
    size_t amount_faces = 0; // How many triangles in the object
    size_t amount_norms = 0;
    size_t len = 0;
    ssize_t chars_read;

    obj result;

    char* line = NULL;
    char** lines = NULL;

    int* faces_temp;
    float* verts_temp;
    float* norms_temp;
    
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open OBJ file '%s'", path);
        exit(EXIT_FAILURE);
    }

    amount_file_lines = get_amount_lines(fp);

    lines = malloc(sizeof(char*) * amount_file_lines);
    rewind(fp);

    // This loop reads in all the lines of the file.
    for (int i = 0; (chars_read = getline(&line, &len, fp)) != -1; i++) {
        lines[i] = malloc(sizeof(char) * chars_read);
        memcpy(lines[i], line, chars_read);
    }

    // This loop calculates the amount of vertices in the file, and the amount of faces too
    for (int i = 0; i < amount_file_lines; i++) {
        switch (lines[i][0]) {
        case 'v':
            if (lines[i][1] == 'n') {
                amount_norms++;
            }
            else {
                amount_vertices++;
            }
            break;
        case 'f':
            amount_faces++;
            break;
        }        
    }

    // Set properties in the obj output
    result.amount_verts = amount_vertices;
    result.amount_tris = amount_faces;
    result.amount_norms = amount_norms;
    result.verts = calloc(sizeof(vec3d), amount_vertices);
    result.tris = calloc(sizeof(tri3d), amount_faces);
    result.norms = calloc(sizeof(vec3d), amount_norms);

    // These two are the current writing place in the arrays
    vec3d* front_verts = result.verts;
    tri3d* front_tris = result.tris;
    vec3d* front_norms = result.norms;

    // This adds all the vertices and faces to the file
    for (int i = 0; i < amount_file_lines; i++) {
        switch (lines[i][0]) {
        case 'v':
            if (lines[i][1] == 'n') {
                norms_temp = parse_normal(lines[i]);
                *front_norms = (vec3d){
                    norms_temp[0], norms_temp[1], norms_temp[2]
                };
                front_norms++;
            } else {
                verts_temp = parse_vertex(lines[i]);
                *front_verts = (vec3d){
                    verts_temp[0],verts_temp[1],verts_temp[2]
                };
                front_verts++;
            }
            break;
        case 'f':
            faces_temp = parse_face(lines[i]);
            *front_tris = (tri3d){
                result.verts[faces_temp[0] - 1],
                result.verts[faces_temp[3] - 1],
                result.verts[faces_temp[6] - 1],
                result.norms[faces_temp[2] - 1],
                result.norms[faces_temp[5] - 1],
                result.norms[faces_temp[8] - 1],
                (material){.diffuse = 0xffffffff}
            };
            front_tris++;
            break;
        }
    }

    fclose(fp);
    free(line);
    for (size_t i = 0; i < amount_file_lines; i++) free(lines[i]);
    free(lines);
    free(faces_temp);
    free(verts_temp);
    free(norms_temp);
    free(fp);
    
    return result;
}

float* parse_vertex(char* s) {
    float* result = calloc(sizeof(int), 3);
    sscanf(s, "v %f %f %f", result, result+1, result+2);
    return result;
}

float* parse_normal(char* s) {
    float* result = calloc(sizeof(int), 3);
    sscanf(s, "vn %f %f %f", result, result+1, result+2);
    return result;
}

int* parse_face(char* s) {
    char* buffer = calloc(sizeof(char), strlen(s));
    char* front_buffer = buffer;
    int* values = calloc(sizeof(int), 9);
    int* front_values = values;

    if (s[0] != 'f') {
        printf("Not a valid face");
        return;
    } else {
        s += 2; // set string pointer to beginning of actual string data
    }

    for (size_t i = 0; i < strlen(s); i++) {
        if (front_values-values >= 9) {
            printf("Too many faces: %s\nSetting values as: ", s);
            printf("%d %d %d %d %d %d %d %d %d\n",
                    values[0],values[1],values[2],values[3],values[4],values[5],values[6],values[7],values[8],values[9]);
            break;
        }
        if (s[i] == ' ' || s[i] == '/' || s[i] == '\n') {
            int value = atoi(buffer);
            if (value == 0) value = -1;
            *front_values = value;
            front_values++;
            memset(buffer, 0, strlen(buffer));
            front_buffer = buffer;
        } else {
            *front_buffer = s[i];
            front_buffer++;
        }
    }
    
    return values;
}
