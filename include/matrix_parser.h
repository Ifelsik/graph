//
// Created by misha on 23.04.2023.
//

#ifndef FLITA2_MATRIX_PARSER_H
#define FLITA2_MATRIX_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_SIZE 5

int getMatrixSize(char **matrix);

int** parseSquareMatrix(char **matrix);

#endif //FLITA2_MATRIX_PARSER_H
