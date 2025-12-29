#include <stdio.h>
#include <string.h>

/* "축하합니다, <username>!"를 버퍼에 작성합니다. 이 버퍼는 호출자가 출력할 것입니다.

@param buffer: 작성할 버퍼
@param buffer_size: 버퍼의 크기
@param userName: 축하할 사용자 이름 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    const char* message_template = "축하합니다, ";
    const char* message_suffix = "!";
    
    // Calculate total length of the message
    int total_length = strlen(message_template) + userName_size + strlen(message_suffix);
    
    // Ensure the total length does not exceed buffer size
    if (total_length >= buffer_size) {
        total_length = buffer_size - 1; // Leave space for null terminator
    }
    
    // Write the message to the buffer
    snprintf(buffer, buffer_size, "%s%s%s", message_template, userName, message_suffix);
}