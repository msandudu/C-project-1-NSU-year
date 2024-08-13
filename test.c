#include <stdio.h>

int main(){
    FILE* input = fopen("smile.png", "rb");
    FILE* output = fopen("new_smile.png", "rb");
    unsigned char c1, c2;
    int cnt = 0, i = 0;
    while (fread(&c1, sizeof(unsigned char), 1, input) == 1) {
        fread(&c2, sizeof(unsigned char), 1, output);
        i++;
        if (c1 != c2){
            cnt++;
        }
    }
    printf("%d", cnt);
}