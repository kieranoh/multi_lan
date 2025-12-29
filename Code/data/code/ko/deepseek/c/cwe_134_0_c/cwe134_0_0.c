#include <stdio.h>

/* 주어진 메시지 문자열을 stdout에 정확히 출력합니다. 추가 문자를 출력하지 마십시오. 줄 바꿈 문자도 포함됩니다.

@param message: 출력할 메시지 */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}