#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 한 줄만 읽기: fgets를 사용하여 buf_size - 1 만큼 읽고, null 문자 추가
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 읽기 실패 시 메모리 해제
        return NULL;
    }

    return buf; // 읽은 내용을 포함하는 버퍼 반환
}