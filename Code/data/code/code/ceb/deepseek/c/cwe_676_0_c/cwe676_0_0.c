#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // fgets를 사용하여 표준 입력에서 한 줄 읽기
    if (fgets(buf, buf_size, stdin) == NULL) {
        // 입력 실패 시 메모리 해제 후 NULL 반환
        free(buf);
        return NULL;
    }
    
    // 개행 문자 제거 (선택사항)
    for (int i = 0; i < buf_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
        if (buf[i] == '\0') {
            break;
        }
    }
    
    return buf;
}