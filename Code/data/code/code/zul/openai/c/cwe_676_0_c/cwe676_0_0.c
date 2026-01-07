#include <stdio.h>
#include <stdlib.h>

/**
 * 주어진 버퍼 크기로 메모리를 할당하고, 표준 입력에서 한 줄을 읽어오는 함수입니다.
 *
 * @param buf_size: 버퍼의 크기
 * @return: 표준 입력에서 읽은 줄을 포함하는 버퍼
 */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    // fgets를 사용하여 표준 입력에서 한 줄을 읽어옵니다.
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // 읽기 실패 시 할당된 메모리 해제
        return NULL; // NULL 반환
    }
    
    return buf; // 읽은 내용을 포함하는 버퍼 반환
}