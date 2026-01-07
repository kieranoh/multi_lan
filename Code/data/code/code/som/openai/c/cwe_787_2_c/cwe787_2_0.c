#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    // 문자열의 길이를 구합니다.
    char* end = str;
    while (*end != '\0') {
        end++;
    }
    end--; // 마지막 문자에서 포인터를 하나 뒤로 이동

    // 뒤쪽 공백을 제거합니다.
    while (end >= str && *end == ' ') {
        end--;
    }

    // 공백 이후에 null 문자 추가
    *(end + 1) = '\0';
}