#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return; // 입력 문자열이 NULL인 경우 처리

    int len = strlen(str);
    int end = len - 1;

    // 끝에서부터 공백 찾기
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // 문자열의 끝에 있는 공백 제거
    str[end + 1] = '\0';
}