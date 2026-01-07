#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    // 포맷 문자열과 유저 이름을 결합하기 위한 최대 길이 계산
    const char* format = "축하합니다, %s!";
    int needed_size = snprintf(NULL, 0, format, userName) + 1; // 필요한 크기 계산

    // 버퍼 크기가 충분한지 확인
    if (needed_size > buffer_size) {
        // 버퍼가 충분하지 않으면, 잘라서 복사
        snprintf(buffer, buffer_size, format, userName); // 버퍼에 작성
    } else {
        // 버퍼가 충분하다면 전체 메시지 작성
        snprintf(buffer, buffer_size, format, userName);
    }
}