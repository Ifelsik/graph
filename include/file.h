//
// Created by misha on 23.04.2023.
//

#ifndef FLITA2_FILE_H
#define FLITA2_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BASE_LEN 256

char* readFile(char *path);

int appendToFile(char *path, char *text);

char** readLinesFromFile(char *path);

#endif //FLITA2_FILE_H
