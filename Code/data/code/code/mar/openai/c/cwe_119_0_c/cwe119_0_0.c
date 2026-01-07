#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // dest의 크기와 src의 크기를 고려하여 복사할 크기를 결정
    int copy_size = (dest_size - 1 < src_size) ? (dest_size - 1) : src_size;
    
    // src의 내용을 dest에 복사
    strncpy(dest, src, copy_size);

    // dest의 마지막에 널 종료 문자 추가
    dest[copy_size] = '\0';
}