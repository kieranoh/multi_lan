#include <stdlib.h>
#include <string.h>

/* 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다. */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1); // +1 for the null terminator
    
    if (copy == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    strcpy(copy, str); // 문자열 복사
    return copy; // 복사된 문자열 반환
}