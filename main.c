#include <stdio.h>
#include <string.h>
#include "main.h"
#include "tree.h"
#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]){
    if (!strcmp("-c", argv[1])){
        compress(argv[2], argv[3]);
    }
    else if (!strcmp("-d", argv[1])){
        decompress(argv[2], argv[3]);
    }
    else if (!strcmp("--help", argv[1])){
        printf("\n\tFollow the next instructions:\n");
        printf("\n\t\tFOR COMPRESSING FILES (without \"<\" and \">\"):\n");
        printf("\thuffman.exe -c <input file> <output file>\n");
        printf("\n\t\tFOR DECOMPRESSING FILES (without \"<\" and \">\"):\n");
        printf("\thuffman.exe -d <input file> <output file>\n\n");
    }
    else {
        printf("\n\twrite <huffman.exe --help> to get instructions (without \"<\" and \">\")\n\n");
    }
    return 0;
}