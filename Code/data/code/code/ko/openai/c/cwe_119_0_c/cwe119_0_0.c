#include <string.h>

/* 가능한 한 src의 내용을 dest로 복사하려면 strncpy를 사용하세요.

@param dest: 목적지 버퍼
@param dest_size: 목적지 버퍼의 크기
@param src: 원본 버퍼
@param src_size: 원본 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // strncpy를 사용하여 src의 내용을 dest로 복사
    strncpy(dest, src, dest_size - 1);
    // dest의 끝을 null 문자로 설정하여 문자열 종료
    dest[dest_size - 1] = '\0';
}