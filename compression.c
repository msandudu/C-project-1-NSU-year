#include "compression.h"

void compress(char *input_file, char *output_file){
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");
    int amount[256] = {0}, not_z_sym = 0;

    printf("\n\tCounting each symbol frequence... (1/4)");

    int in_size = count(input, amount), out_size;
    Symbol *dict[256];
    
    printf("\n\tPreparing... (2/4)");
    Tree *tree = huffman(amount);

    for (int i = 0; i < 256; i++){
        dict[i] = malloc(sizeof(Symbol));
        dict[i]->code = 0;
        dict[i]->size = 0;
        if (amount[i] > 0){
            not_z_sym++;
        }
    }

    printf("\n\tMaking code... (3/4)");
    make_code(tree, dict, 0, 0);

    printf("\n\tMaking compressed file... (4/4)");

    rewind(input);
    out_size = write_compression(input, output, amount, dict, not_z_sym, in_size);
    fclose(input);
    fclose(output);
    printf("\n\tDone! Compression rate: %.3f%%\n\n", 100 - (double)out_size/(double)in_size * 100);
    destroy(tree);
}

int write_compression(FILE *input, FILE *output, int *amount, Symbol **dict, int not_z_sym, int in_size){
    int size = 0;
    fwrite(&in_size, sizeof(int), 1, output);
    fwrite(&not_z_sym, sizeof(int), 1, output);
    size += 64;
    for (int i = 0; i < 256; i++) {
        if (amount[i] > 0) {
            fwrite(&i, sizeof(unsigned char), 1, output);
            size += 8;
            fwrite(&amount[i], sizeof(int), 1, output);
            size += 32;
        }
    }

    unsigned char c, code = 0;
    unsigned int buffer = 0, buf_size = 0;
    while(fread(&c, sizeof(unsigned char), 1, input) == 1) {
        buffer <<= dict[c]->size;
        buffer = buffer | dict[c]->code;
        buf_size += dict[c]->size;

        while (buf_size > 7){
            buf_size -= 8;
            code = (unsigned char)((buffer >> buf_size) & ((2 << 8) - 1));
            fwrite(&code, sizeof(unsigned char), 1, output);
            size += 8;
        }
    }
    if (buf_size > 0){
        code = (buffer << (8 - buf_size)) & ((2 << 8) - 1);
        fwrite(&code, sizeof(unsigned char), 1, output);
        size += 8;
    }
    return size;
}