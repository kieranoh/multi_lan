#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // fgets를 사용하여 표준 입력에서 한 줄 읽기
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    return buf;
}