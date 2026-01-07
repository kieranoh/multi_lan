#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* dest_size가 1이면 null-terminator만 저장할 수 있음 */
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    /* 복사할 최대 문자 수 계산: dest_size-1 또는 src_size 중 작은 값 */
    int copy_len = dest_size - 1;
    if (src_size < copy_len) {
        copy_len = src_size;
    }
    
    /* strncpy를 사용하여 복사 */
    strncpy(dest, src, copy_len);
    
    /* strncpy는 null-terminator를 보장하지 않으므로 명시적으로 추가 */
    dest[copy_len] = '\0';
}