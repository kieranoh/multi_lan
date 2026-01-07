#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    // 포인터를 사용하여 문자열의 끝으로 이동
    char* end = str;
    while (*end != '\0') {
        end++;
    }
    end--; // 마지막 널 문자 전으로 이동

    // 끝에서부터 공백 제거
    while (end >= str && *end == ' ') {
        end--;
    }
    
    // 공백 다음에 널 문자 추가
    *(end + 1) = '\0';
}