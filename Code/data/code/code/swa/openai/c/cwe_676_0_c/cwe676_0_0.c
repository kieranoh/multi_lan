#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // 한 줄을 읽기 위해 fgets 사용
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // fgets 실패할 경우 메모리 해제
        return NULL;
    }
    
    return buf; // 읽은 내용을 포함하는 버퍼 반환
}