#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int length = strlen(str);
    int end = length - 1;

    // 공백을 제거할 위치 찾기
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // 문자열의 끝을 null 문자로 설정하여 공백 제거
    str[end + 1] = '\0';
}