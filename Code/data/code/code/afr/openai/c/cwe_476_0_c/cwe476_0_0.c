#include <stdlib.h>
#include <string.h>

/*
 요청된 버퍼 크기를 기준으로 해당 크기의 버퍼를 할당하고,
 버퍼의 처음과 마지막 10바이트에 'A'를 씁니다.

 @param buf_size: 할당할 버퍼의 크기
 @return 할당된 버퍼 
*/
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // 버퍼 크기가 너무 작으면 NULL 반환
    }

    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 초기화: 버퍼의 모든 바이트를 0으로 설정
    memset(buffer, 0, buf_size);

    // 처음 10바이트에 'A' 쓰기
    memset(buffer, 'A', 10);

    // 마지막 10바이트에 'A' 쓰기
    memset(buffer + buf_size - 10, 'A', 10);

    return buffer;
}