#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    int length = strlen(str);
    int i;

    // 오른쪽 끝에서부터 공백을 찾기
    for (i = length - 1; i >= 0 && str[i] == ' '; i--) {
        // 아무것도 하지 않음
    }

    // 공백을 제거하고 문자열 종료
    str[i + 1] = '\0';
}