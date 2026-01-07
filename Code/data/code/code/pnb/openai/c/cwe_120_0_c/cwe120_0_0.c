#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 버퍼는 호출자가 출력할 것입니다.
@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *message = "축하합니다, ";
    int message_length = strlen(message);
    
    // Check if the buffer can hold the message and username
    if (buffer_size <= message_length + userName_size + 1) {
        return; // Not enough space in the buffer
    }

    // Copy the message into the buffer
    strcpy(buffer, message);

    // Append the username to the buffer
    strncat(buffer, userName, userName_size);
    
    // Append the exclamation mark
    strcat(buffer, "!");
}