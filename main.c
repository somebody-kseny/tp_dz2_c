#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "include/search.h"
#include "include/enum.h"

#define TIME_MEASURE 1

// Seq read_from(FILE*, FILE*);
long int mks_time();

int main(int argc, char *argv[]) {
    FILE* out = stdout;

    if (argc != 2){
        fprintf(out, "Необходимо передать, откуда брать входные данные: имя файла или console\n");
        return FALSE;
    }

    FILE* in;
    if ( !strcmp(argv[1], "console") ) {
        in = stdin;
    } else {
        if ((in = fopen(argv[1], "r")) == NULL) {
            fprintf(out, "Не найден / не могу открыть входной файл\n");
            return FALSE;
        }
    }

    //Seq seq = read_from(in, out);

    int length;
    int scanned = fscanf(in, "%i", &length);
    if ((scanned != 1)||(length < 0)){
        fprintf(out, "Неверный ввод. Сначала необходимо ввести длину буфера.\n");
        return(FALSE);
    }
    //fprintf(out, "compare length = %i, INT_MAX = %i\n", length, INT_MAX);
    Seq seq;
    seq.len = length;
    size_t size = length * sizeof(char);
    seq.buf = (char*)malloc(size);
    if (!seq.buf){
        fprintf(out, "malloc не сработал.\n");
        return(FALSE);
    }
    fread(seq.buf, length, sizeof(char), in);
    //printf("nop %s\n", buf);
    




    StartEnd st_end;

    long int time[TIME_MEASURE];
    for (int i = 0; i < TIME_MEASURE; i++){
        time[i] = mks_time();
        st_end = find_max_seq(seq);
        time[i] = mks_time() - time[i];
    }
    long double average_time = 0;
    for (int i = 0; i < TIME_MEASURE; i++){
        average_time += time[i];
    }
    average_time = average_time/TIME_MEASURE;

    fprintf(out, "time: %Lf\noutput: %i %i\n", average_time, st_end.start, st_end.end);
    //fprintf(out, "Самая длинная последовательность начинается на символе %i,  заканчивается %i\n", st_end.start, st_end.end);
    free (seq.buf);
    return TRUE;
}

long int mks_time()
{
  struct timespec t;

  clock_gettime(CLOCK_REALTIME, &t);
  long mt = (long)t.tv_sec * 1000000 + t.tv_nsec / 1000;
  return mt;
}