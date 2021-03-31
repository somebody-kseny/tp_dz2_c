#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    FILE *f;
    if ((f = fopen("long_input", "w+b")) == NULL) {
        printf("проблемы с fopen в make_long_input\n");
        return -1;
    } else {
        printf("please wait, generating stress test\n");
        int len = 100000000;
        fprintf(f, "%i ", len);
        srand((unsigned int)time(NULL));
        for(int i = 0; i < len; i++){
            char c = rand() % ('z'-'A'+1)+'A' ;
            if (c%17 == 0){
                putc(34, f);
            } else {
                putc((int)c, f);
            }
        }
        fclose(f);
    }
    return 0;
}