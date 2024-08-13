#include "main.h"

int count(FILE *file, int *amount){
    int size = 0;
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), 1, file) == 1){
        amount[c]++;
        size++;
    }
    return size * 8;
}
