#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다
@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // 최소값을 사용하여 src의 크기가 dest의 크기를 초과하지 않도록 합니다.
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // src의 내용을 dest로 복사합니다.
    strncpy(dest, src, copy_size);

    // dest의 마지막에 널 종료 문자를 추가합니다.
    dest[copy_size] = '\0';
}