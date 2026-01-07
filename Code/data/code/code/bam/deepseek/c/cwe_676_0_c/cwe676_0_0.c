#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_stdin_to_buffer(int buf_size) {
    if (buf_size <= 0) {
        return NULL;
    }
    
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // 버퍼 초기화
    memset(buf, 0, buf_size);
    
    // 표준 입력에서 한 줄 읽기
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    // 개행 문자 제거 (선택적)
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    
    return buf;
}