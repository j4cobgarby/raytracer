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

obj read_OBJ(const char* path) {
    FILE* fp;

    size_t amount_file_lines = 0;
    size_t amount_vertices = 0; // The amount of vertices in the object. Indices to these are started at 1
    size_t amount_faces = 0; // How many triangles in the object
    size_t len = 0;
    ssize_t chars_read;

    obj result;

    char* line = NULL;
    char** lines = NULL;

    int* faces_temp;
    float* verts_temp;
    
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open OBJ file '%s'", path);
        exit(EXIT_FAILURE);
    }

    amount_file_lines = get_amount_lines(fp);

    printf("Amount of lines: %ld\n", amount_file_lines);
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
            if (lines[i][1] == 'n') break;
            amount_vertices++;
            break;
        case 'f':
            amount_faces++;
            break;
        }        
    }

    // Set properties in the obj output
    result.amount_verts = amount_vertices;
    result.amount_tris = amount_faces;
    result.verts = calloc(sizeof(vec3d), amount_vertices);
    result.tris = calloc(sizeof(tri3d), amount_faces);

    // These two are the current writing place in the arrays
    vec3d* front_verts = result.verts;
    tri3d* front_tris = result.tris;

    // This adds all the vertices and faces to the file
    for (int i = 0; i < amount_file_lines; i++) {
        switch (lines[i][0]) {
        case 'v':
            if (lines[i][1] == 'n') break;
            verts_temp = parse_vertex(lines[i]);
            *front_verts = (vec3d){
                verts_temp[0],verts_temp[1],verts_temp[2]
            };
            front_verts++;
            break;
        case 'f':
            faces_temp = parse_face(lines[i]);
            printf(" == == == == %d, %d, %d\n", faces_temp[0]-1, faces_temp[3]-1, faces_temp[6]-1);
            printf("\t -> %f, %f, %f\n", result.verts[faces_temp[0] - 1].x,
                    result.verts[faces_temp[0] - 1].y,
                    result.verts[faces_temp[0] - 1].z);
            *front_tris = (tri3d){
                result.verts[faces_temp[0] - 1],
                result.verts[faces_temp[3] - 1],
                result.verts[faces_temp[6] - 1],
                (material){.diffuse = 0xff0000ff}
            };
            front_tris++;
            break;
        }
    }

    printf("Amount of vertices: %d\nAmount of tris: %d\n", amount_vertices, amount_faces);

    for (int i = 0; i < amount_vertices; i++) {
        vec3d_print(result.verts[i]);
    }

    for (int i = 0; i < amount_faces; i++) {
        tri3d_print(result.tris[i]);
    }

    fclose(fp);

    return result;
}

float* parse_vertex(char* s) {
    float* result = calloc(sizeof(int), 3);
    sscanf(s, "v %f %f %f", result, result+1, result+2);
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
            printf("Too many!\n");
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
