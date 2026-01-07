#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 씁니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 쓸 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_format = "축하합니다, ";
    const char* message_suffix = "!";
    int total_length = strlen(message_format) + userName_size + strlen(message_suffix);

    if (total_length >= buffer_size) {
        // 버퍼가 부족할 경우, 잘리도록 설정
        snprintf(buffer, buffer_size, "%s%s", message_format, userName);
        strncat(buffer, message_suffix, buffer_size - strlen(buffer) - 1);
    } else {
        snprintf(buffer, buffer_size, "%s%s%s", message_format, userName, message_suffix);
    }
}