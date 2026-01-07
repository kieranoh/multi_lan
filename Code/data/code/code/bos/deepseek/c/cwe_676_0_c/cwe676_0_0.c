#include <stdio.h>
#include <stdlib.h>

/* 지정된 버퍼 크기를 사용하여 버퍼를 할당하고 표준 입력에서 한 줄만 버퍼로 읽습니다.

@param buf_size: 버퍼의 크기
@return 표준 입력에서 읽은 줄을 포함하는 버퍼 */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    return buf;
}