#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include "tree.h"
#include "main.h"

void decompress(char *input_file, char *output_file);
int read_key(FILE *input, int *amount);
void write_decompression(FILE *input, FILE *output, Tree *tree, int in_size);

#endif