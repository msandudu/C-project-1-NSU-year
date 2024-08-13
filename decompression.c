#include "decompression.h"

void decompress(char *input_file, char *output_file){
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");
    int amount[256] = {0}, in_size = 0;
    Symbol *dict[256];

    printf("\n\tReading key to decode... (1/3)");
    in_size = read_key(input, amount);

    printf("\n\tDecoding... (2/3)");
    Tree *tree = huffman(amount);

    for (int i = 0; i < 256; i++) {
        dict[i] = malloc(sizeof(Symbol));
        dict[i]->code = 0;
        dict[i]->size = 0;
    }

    make_code(tree, dict, 0, 0);
    printf("\n\tMaking decompressed file... (3/3)");

    write_decompression(input, output, tree, in_size);

    printf("\n\tDone!\n\n");
    destroy(tree);

    fclose(input);
    fclose(output);
}

int read_key(FILE *input, int *amount) {
    int not_z_sym = 0, in_size;
    unsigned char c;
    int cnt;

    fread(&in_size, sizeof(int), 1, input);
    fread(&not_z_sym, sizeof(int), 1, input);

    for (int i = 0; i < not_z_sym; i++){
        fread(&c, sizeof(unsigned char), 1, input);
        fread(&cnt, sizeof(int), 1, input);
        amount[c] = cnt;
    }
    return in_size;
}

void write_decompression(FILE *input, FILE *output, Tree *tree, int in_size){
    unsigned int buffer = 0, buf_size = 0;
    unsigned char c = 0;
    Tree *leaf;

    while(fread(&c, sizeof(unsigned char), 1, input) == 1 && in_size > 0){
        buffer = buffer << 8;
        buffer = buffer | c;
        buf_size += 8;
        while ((leaf = find_code(tree, buffer, buf_size, 0)) != NULL && in_size > 0){
            fwrite(&leaf->elem, sizeof(unsigned char), 1, output);
            in_size -= 8;
            buf_size -= leaf->size;
        }
    }
}