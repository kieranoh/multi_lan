#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 씁니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 쓸 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    // Format the congratulatory message
    const char *message_format = "축하합니다, %s!";
    int required_size = snprintf(NULL, 0, message_format, userName);

    // Check if the buffer is large enough
    if (required_size + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // Handle the case where the buffer is too small
        snprintf(buffer, buffer_size, "버퍼가 너무 작습니다!");
    }
}