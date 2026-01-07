#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // dest_size가 1이면 null 문자만 저장 가능
    if (dest_size == 1) {
        dest[0] = '\0';
        return;
    }
    
    // 복사할 최대 길이 계산: dest_size-1 (null 문자 공간 확보)와 src_size 중 작은 값
    int copy_len = (dest_size - 1) < src_size ? (dest_size - 1) : src_size;
    
    // strncpy를 사용하여 복사
    strncpy(dest, src, copy_len);
    
    // strncpy는 null 문자를 보장하지 않으므로 명시적으로 추가
    dest[copy_len] = '\0';
}