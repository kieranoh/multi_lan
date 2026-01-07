#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    int len = strlen(str);
    int index = len - 1;

    // 공백을 찾기 위해 문자열의 끝에서부터 탐색
    while (index >= 0 && str[index] == ' ') {
        index--;
    }

    // 문자열 끝에 있는 공백을 제거
    str[index + 1] = '\0';
}