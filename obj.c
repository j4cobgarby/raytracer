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
    size_t amount_vertices = 0;
    size_t amount_faces = 0;
    size_t len = 0;
    ssize_t chars_read;

    char* line = NULL;
    char** lines = NULL;
    
    fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Failed to open OBJ file '%s'", path);
        exit(EXIT_FAILURE);
    }

    amount_file_lines = get_amount_lines(fp);

    printf("Amount of lines: %ld\n", amount_file_lines);
    lines = malloc(sizeof(char*) * amount_file_lines);
    rewind(fp);

    for (int i = 0; (chars_read = getline(&line, &len, fp)) != -1; i++) {
        lines[i] = malloc(sizeof(char) * chars_read);
        memcpy(lines[i], line, chars_read - 1);
        i++;
    }

    for (int i = 0; i < amount_file_lines; i++) {
        printf("%s\n", lines[i]);
    }

    fclose(fp);
}
