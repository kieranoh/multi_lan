#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // stdin에서 한 줄을 읽어옵니다.
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 읽기에 실패하면 메모리 해제
        return NULL;
    }

    return buf; // 읽은 줄이 포함된 버퍼 반환
}