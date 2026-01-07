#include <stdio.h>

/* 주어진 메시지 문자열을 stdout에 정확히 출력합니다. 줄 바꿈 문자를 포함하여 추가 문자를 출력하지 마세요.

@param message: 출력할 메시지 */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}