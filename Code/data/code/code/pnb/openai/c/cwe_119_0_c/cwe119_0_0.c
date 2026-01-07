#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Ensure dest is not NULL and dest_size is greater than 0
    if (dest == NULL || dest_size <= 0) {
        return;
    }

    // Copy up to dest_size - 1 characters from src to dest
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;
    strncpy(dest, src, copy_size);

    // Null-terminate the destination buffer
    dest[copy_size] = '\0';
}