//
// Created by misha on 20.04.2023.
//

#include "../include/file.h"

/*
 @brief Exit statuses:
 */
char* readFile(char *path) {
    FILE *file_p = NULL;
    char *filebuf = NULL;
    int file_size = 0;
    char c = 0;
    file_p = fopen(path, "rb");
    assert(file_p != NULL);

    fseek(file_p, 0, SEEK_END);
    file_size = ftell(file_p);
    fseek(file_p, 0, SEEK_SET);
    filebuf = (char*) malloc(sizeof(char) * file_size);
    if (NULL == filebuf) {
        fclose(file_p);
        exit(2);
    }
    /* Doesn't work in Windows!!!
    fread(*filebuf, sizeof(char), file_size, file_p);
    fclose(file_p);
     */
    // For win
    for (int i = 0; i < file_size; i++) {
        c = (char) fgetc(file_p);
        if (c != '\r')
            filebuf[i] = c;
        else
            filebuf[i] = ' ';
    }
    filebuf[file_size] = '\0';
    //
    
    fclose(file_p);
    return filebuf;
}

/*
 
 */
int appendToFile(char *path, char *text) {
    FILE *file_p = NULL;
    int status = 0;
    file_p = fopen(path, "a+");
    if (NULL == file_p) {
        fclose(file_p);
        return 1;
    }
    status = fputs(text, file_p);
    if (status == EOF) {
        fclose(file_p);
        return -1;
    }
    fclose(file_p);
    return 0;
}

/*
 
 */
char** readLinesFromFile(char *path) {
    FILE *file_p = NULL;
    char *filebuf = NULL;
    char **lines = NULL;
    int number_of_lines = 0;
    file_p = fopen(path, "r");
    
    assert(file_p != NULL);

    filebuf = readFile(path);
    for (int i = 0; filebuf[i] != '\0'; i++) {
        if (filebuf[i] == '\n' || filebuf[i + 1] == '\0')
            number_of_lines++;
    }

    lines = (char**) malloc(sizeof (char*) * number_of_lines);
    for (int i = 0; i < number_of_lines; i++) {
        int base_len = BASE_LEN;
        int line_length = 0;
        int c = 0;
        lines[i] = (char*) malloc(sizeof(char) * base_len);
        while ((c = fgetc(file_p)) != '\n' && c != EOF) {
            lines[i][line_length] = (char) c;
            line_length++;
            if (line_length >= base_len) {
                base_len *= 2;
                lines[i] = (char*) realloc(lines[i], base_len);
                if (NULL == lines[i]) {
                    fclose(file_p);
                    exit(2);
                }
            }
        }
        lines[i][line_length] = '\0';
    }
    fclose(file_p);
    return lines;
}