#include <stdio.h>

/**
 * 주어진 메시지 문자열을 정확히 stdout에 출력합니다.
 * 추가 문자, 특히 새 줄 문자를 출력하지 않습니다.
 * 
 * @param message: 출력할 메시지
 */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}