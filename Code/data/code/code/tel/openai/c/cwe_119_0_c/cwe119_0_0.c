#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // dest_size가 0이면 아무 것도 복사하지 않음
    if (dest_size <= 0) {
        return;
    }

    // src_size가 dest_size보다 크면 dest_size - 1만큼만 복사
    int bytes_to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // src의 내용을 dest로 복사
    strncpy(dest, src, bytes_to_copy);

    // null 문자로 dest의 끝을 마감
    dest[bytes_to_copy] = '\0';
}