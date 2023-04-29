//
// Created by misha on 23.04.2023.
//

#ifndef FLITA2_FILE_H
#define FLITA2_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BASE_LEN 256

int readFile(char *path, char **filebuf);

int appendToFile(char *path, char *text);

int readLinesFromFile(char *path, char ***lines);

#endif //FLITA2_FILE_H
