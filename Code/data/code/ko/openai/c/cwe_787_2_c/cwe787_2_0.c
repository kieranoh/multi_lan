#include <stdio.h>

void trim_spaces(char* str) {
    char* end;

    // 공백이 아닌 마지막 문자를 찾습니다.
    end = str;
    while (*end) {
        end++;
    }
    end--; // end는 마지막 문자로 이동합니다.

    // 후행 공백을 제거합니다.
    while (end >= str && *end == ' ') {
        end--;
    }

    // 문자열의 끝을 후행 공백 다음 문자에 설정합니다.
    *(end + 1) = '\0';
}