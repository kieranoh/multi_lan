#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* dest_size가 1이면 null-terminator만 저장 가능 */
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    /* 복사할 최대 문자 수 계산: dest_size-1 (null-terminator 공간 확보) */
    int max_copy = dest_size - 1;
    
    /* src_size가 0보다 크면 src_size와 max_copy 중 작은 값만큼 복사 */
    if (src_size > 0) {
        int copy_len = src_size < max_copy ? src_size : max_copy;
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';
    } else {
        /* src_size가 0 이하이면 빈 문자열로 설정 */
        dest[0] = '\0';
    }
}