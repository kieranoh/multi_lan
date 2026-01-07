#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다. */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // NULL 포인터 처리
    }

    // 문자열 길이를 계산하고 메모리를 할당합니다.
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1); // +1은 null 종단자를 위한 공간

    if (copy == NULL) {
        return NULL; // 메모리 할당 실패 처리
    }

    // 원본 문자열을 복사합니다.
    strcpy(copy, str);
    return copy; // 복사된 문자열을 반환합니다.
}