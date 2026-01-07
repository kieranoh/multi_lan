#include <stdio.h>
#include <stdlib.h>

/* 버퍼 크기를 주어지면, 버퍼를 할당하고 표준 입력에서 한 줄만 버퍼에 읽어옵니다.
@param buf_size: 버퍼의 크기
@return 표준 입력에서 읽은 줄을 포함하는 버퍼 */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // 한 줄을 읽어오기
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 읽기 실패 시 메모리 해제
        return NULL;
    }

    return buf; // 성공적으로 읽은 줄 반환
}