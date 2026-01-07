#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest로 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Check for valid destination buffer size
    if (dest_size <= 0) {
        return;
    }

    // Calculate the size to copy
    int to_copy = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // Use strncpy to copy contents from src to dest
    strncpy(dest, src, to_copy);

    // Null-terminate the destination string
    dest[to_copy] = '\0';
}