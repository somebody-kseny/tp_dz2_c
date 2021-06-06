typedef struct Seq {
    char* buf;
    int len;
} Seq;

typedef struct StartEnd {
    int start;
    int end;
} StartEnd;

StartEnd find_max_seq(Seq);