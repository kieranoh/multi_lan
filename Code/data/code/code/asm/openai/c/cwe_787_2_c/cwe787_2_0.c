#include <stddef.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    // 문자열의 끝을 가리키는 포인터
    char* end = str;

    // 문자열 끝으로 이동하여 마지막 문자가 공백인지 확인
    while (*end) {
        end++;
    }
    end--; // 마지막 문자의 포인터로 조정

    // 끝에서부터 공백이 아닌 문자를 찾기
    while (end >= str && *end == ' ') {
        end--;
    }

    // 끝을 널 종료 문자로 변경하여 문자열 수정
    *(end + 1) = '\0';
}