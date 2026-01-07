#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당에 실패한 경우 NULL 반환
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 읽기 실패 시 할당된 메모리 해제
        return NULL;
    }
    
    return buf; // 성공적으로 버퍼에 읽은 내용을 반환
}