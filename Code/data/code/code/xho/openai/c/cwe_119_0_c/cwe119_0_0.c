#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다
@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Ensure that we do not exceed the size of the destination buffer
    if (dest_size <= 0) {
        return;
    }
    
    // Use strncpy to copy the content from src to dest
    // Ensure to copy only up to dest_size - 1 to leave space for the null terminator
    strncpy(dest, src, dest_size - 1);
    
    // Null-terminate the destination buffer
    dest[dest_size - 1] = '\0';
}