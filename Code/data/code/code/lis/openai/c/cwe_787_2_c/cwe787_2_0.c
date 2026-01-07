#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return; // 문자열이 NULL인 경우 아무 작업도 하지 않음
    }
    
    size_t len = strlen(str);
    size_t end = len;

    // 문자열의 끝에서부터 공백을 찾음
    while (end > 0 && (str[end - 1] == ' ' || str[end - 1] == '\t')) {
        end--;
    }

    // 공백이 발견되면 문자열의 끝을 NULL 문자로 설정
    str[end] = '\0';
}