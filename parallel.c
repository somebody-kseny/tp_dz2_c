#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include "include/search.h"
#include "include/enum.h"
#define MAX_BUF_TO_SEND 30

static int send_to_parent(int * fd_num, const int start, const int end);
static int get_from_child(int * fd_num, StartEnd *se_res);
static StartEnd find_in_child(char*, int, int);
static int get_res(StartEnd *, const int, const int);

StartEnd find_max_seq(Seq input){
    
    //int num_of_process = sysconf(_SC_NPROCESSORS_ONLN)-1;
    int num_of_process = 5;
    int len_part_std = input.len / num_of_process;

    char* seq_part;
    int len_parts_before;
    int len_part;
    int return_fork;
    int fd[num_of_process][2];

    for (int j = 0; j < num_of_process; j++){

        len_part = len_part_std;
        if (j == num_of_process - 1) {
            len_part = input.len - ((num_of_process - 1) * len_part_std);
        }

        len_parts_before = j * len_part_std;
        seq_part = input.buf + len_parts_before;

        if ( pipe(fd[j]) )
        {
            fprintf(stderr,"Не удалось открыть pipe.\n");
        }
        
        return_fork = fork();
        if (return_fork == 0) {
            StartEnd from_child = find_in_child(seq_part, len_part, len_parts_before);
            send_to_parent(fd[j], from_child.start, from_child.end);
            exit(0);
        } else if (return_fork < 0){
            fprintf(stderr,"Не удалось выполнить fork.\n");
        }
    }
    StartEnd se_res = {-1, -1};
    for(int i = 0; i < num_of_process; i++){
        get_from_child(fd[i], &se_res);
    }
    return se_res;
}

static StartEnd find_in_child(char* seq_part, int len_part, int len_parts_before){
    int start = -1;
    int end = -1;
    for (int i = 0; i < len_part; i++){
        if ((seq_part[i] == '"') && (seq_part[i+1] >= 'A') && (seq_part[i+1] <= 'Z')){
            start = i + len_parts_before;
            break;
        }
    }

    for (int i = len_part - 1; i >= 0; i--){
        if (seq_part[i] == '"'){
            end = i + len_parts_before;
            break;
        }
    }
    StartEnd se_return = {start, end};
    return se_return;
}

static int send_to_parent(int * fd_num, const int start, const int end){
    close(fd_num[0]);
    char message[MAX_BUF_TO_SEND];
    sprintf(message, "%i %i", start, end);
    if ((write(fd_num[1], &message, MAX_BUF_TO_SEND)) != MAX_BUF_TO_SEND){
        fprintf(stderr, "problemes with send in child\n");
    };
    if (close(fd_num[1])) {
        fprintf(stderr, "CHILD: Failed to close write pipe\n");
    };
    return TRUE;
}

static int get_from_child(int * fd_num, StartEnd * se_res ){
    if (close(fd_num[1])) {
        fprintf(stderr, "PARENT: Failed to close write pipe\n");
    }
    char message [MAX_BUF_TO_SEND];
    if (read(fd_num[0], message, MAX_BUF_TO_SEND) < 0) {
        fprintf(stderr, "PARENT: Failed to read from pipe\n");
    } else {
        int buf_start = 0;
        int buf_end = 0;
        sscanf(message, "%i %i", &buf_start, &buf_end);
        get_res(se_res, buf_start, buf_end);
    } 
    if (close(fd_num[0])) {
        fprintf(stderr, "PARENT: Failed to close read pipe\n");
    }
    return TRUE;
}

static int get_res(StartEnd *se_res, const int buf_start, const int buf_end){
    if (se_res->start == -1){
        se_res->start = buf_start;
    }
    if (buf_end > se_res->end){
        se_res->end = buf_end;
    }
    return TRUE;
}