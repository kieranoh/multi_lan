#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    // 문자열의 길이를 구합니다.
    char *end = str;
    while (*end) {
        end++;
    }
    // 끝에서부터 공백을 제거합니다.
    while (end > str && (*(end - 1) == ' ' || *(end - 1) == '\t')) {
        end--;
    }
    *end = '\0'; // 문자열 끝을 설정합니다.
}