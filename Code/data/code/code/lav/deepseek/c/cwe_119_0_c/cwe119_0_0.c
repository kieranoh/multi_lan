#include <string.h>

/* strncpy를 사용하여 src의 내용을 가능한 한 많이 dest로 복사합니다

@param dest: 대상 버퍼
@param dest_size: 대상 버퍼의 크기
@param src: 소스 버퍼
@param src_size: 소스 버퍼의 크기 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // 복사할 수 있는 최대 길이 계산
    // dest_size-1은 NULL 종료 문자를 위한 공간
    int copy_size = dest_size - 1;
    
    // src_size가 더 작으면 src_size만큼만 복사
    if (src_size < copy_size) {
        copy_size = src_size;
    }
    
    // strncpy를 사용하여 복사
    strncpy(dest, src, copy_size);
    
    // NULL 종료 보장
    dest[copy_size] = '\0';
}