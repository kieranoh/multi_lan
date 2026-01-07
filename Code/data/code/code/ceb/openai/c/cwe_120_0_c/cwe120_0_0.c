#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Format the congratulatory message
    const char *message_template = "축하합니다, %s!";
    int needed_size = snprintf(NULL, 0, message_template, userName);

    // Check if the buffer is large enough
    if (needed_size + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // If buffer is not enough, we can choose to handle it (e.g., truncating)
        snprintf(buffer, buffer_size, message_template, userName); // will truncate if too long
    }
}