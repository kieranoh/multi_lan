#include <string.h>

/* strncpy를 사용하여 src의 내용을 dest에 최대한 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // 복사할 최대 길이 계산: dest_size-1 (널 종결자를 위한 공간)과 src_size 중 작은 값
    int copy_len = dest_size - 1;
    if (src_size < copy_len) {
        copy_len = src_size;
    }
    
    if (copy_len > 0) {
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';  // 항상 널 종결
    } else {
        dest[0] = '\0';  // 복사할 내용이 없으면 빈 문자열로 설정
    }
}