#include <stdio.h>
#include <stdlib.h>

/* 버퍼 크기를 주어지면, 버퍼를 할당하고 표준 입력에서 한 줄만 버퍼에 읽어옵니다.

@param buf_size: 버퍼의 크기
@return 표준 입력에서 읽은 줄을 포함하는 버퍼 */
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
    
    // 개행 문자 제거 (선택사항)
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    
    return buf;
}