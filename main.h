#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Symbol{
    int code, size;
} Symbol;
int count(FILE *file, int *amount);

#endif