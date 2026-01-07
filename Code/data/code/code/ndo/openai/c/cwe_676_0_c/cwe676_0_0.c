#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 입력 오류 시 할당된 메모리 해제
        return NULL; // 읽기에 실패했을 경우 NULL 반환
    }
    
    return buf; // 읽은 줄이 포함된 버퍼 반환
}