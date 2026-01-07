#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    // "축하합니다, "의 길이
    const char* greeting = "축하합니다, ";
    int greeting_length = strlen(greeting);
    
    // 사용자 이름의 길이
    int user_name_length = userName_size; // 사용자 이름의 길이는 주어진 크기로부터 얻음

    // 결과 문자열의 전체 길이
    int total_length = greeting_length + user_name_length + 1; // +1 for null terminator

    // 버퍼 크기가 충분한지 확인
    if (total_length > buffer_size) {
        // 버퍼가 충분하지 않은 경우, 에러 처리 또는 부분적으로 작성할 수 있음
        snprintf(buffer, buffer_size, "버퍼가 충분하지 않습니다.");
    } else {
        // 버퍼에 문자열 작성
        snprintf(buffer, buffer_size, "%s%s!", greeting, userName);
    }
}