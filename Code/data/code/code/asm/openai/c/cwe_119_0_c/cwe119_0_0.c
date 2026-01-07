#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // 복사할 최대 크기를 결정
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // src의 내용을 dest로 복사
    strncpy(dest, src, copy_size);
    
    // dest의 마지막에 null 종료 문자 추가
    dest[copy_size] = '\0';
}