#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 실패 시 NULL 반환
    }
    
    // 한 줄을 읽어오는 fgets 사용
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 실패 시 메모리 해제
        return NULL; // NULL 반환
    }
    
    return buf; // 읽은 줄이 포함된 버퍼 반환
}