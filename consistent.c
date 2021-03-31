#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/search.h"
#include "include/enum.h"

StartEnd find_max_seq(Seq input){
    char* seq = input.buf;
    int len = input.len;
    int start = -1;
    for (int i = 0; i < len; i++){
        if ((seq[i] == '"') && (seq[i+1] >= 'A') && (seq[i+1] <= 'Z')){
            start = i;
            break;
        }
    }
    int end = -1;
    for (int i = len - 1; i >= 0; i--){
        if (seq[i] == '"'){
            end = i;
            break;
        }
    }
    //printf("start: %i, end: %i\n", start, end);
    StartEnd st_end = {start, end};
    return st_end;
}
