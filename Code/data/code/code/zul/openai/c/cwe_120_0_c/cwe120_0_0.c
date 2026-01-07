#include <stdio.h>
#include <string.h>

/*
 * "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
 *
 * @param buffer: 작성할 버퍼
 * @param buffer_size: 버퍼의 크기
 * @param userName: 축하할 사용자 이름
 * @param userName_size: 사용자 이름의 크기
 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    // 형식 문자열 준비
    const char* message_template = "축하합니다, %s!";
    // 최대 작성할 수 있는 크기 계산
    int message_length = snprintf(NULL, 0, message_template, userName);
    
    // 버퍼 크기가 충분한지 확인
    if (message_length + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // 버퍼가 작으면 오류 처리 (예: 빈 문자열 작성)
        buffer[0] = '\0';
    }
}