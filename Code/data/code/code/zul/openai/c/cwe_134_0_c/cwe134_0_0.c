#include <stdio.h>

/* 주어진 메시지 문자열을 정확히 stdout에 출력합니다. 추가 문자, 특히 새 줄 문자를 출력하지 마세요.

@param message: 출력할 메시지 */
void print_message(const char* message) {
    // 출력할 메시지의 길이를 계산
    int length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // 메시지를 stdout에 출력
    fwrite(message, sizeof(char), length, stdout);
}