#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "tree.h"
#include "main.h"

void compress(char *input_file, char *output_file);
int write_compression(FILE *input, FILE *output, int *amount, Symbol **dict, int not_z_sym, int in_size);

#endif