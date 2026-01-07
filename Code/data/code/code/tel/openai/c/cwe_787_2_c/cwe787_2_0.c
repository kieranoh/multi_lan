#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    int len = strlen(str);
    int end = len - 1;

    // 공백이 있는 끝에서부터 찾기
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // 다음에 null 문자 추가
    str[end + 1] = '\0';
}