#include <stdio.h>
#include <string.h>

/* 将 "恭喜，<username>！" 写入缓冲区。缓冲区将由调用者打印。

@param buffer: 要写入的缓冲区
@param buffer_size: 缓冲区的大小
@param userName: 要祝贺的用户名 */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    const char *message_format = "恭喜，%s！";
    int needed_size = snprintf(NULL, 0, message_format, userName);
    
    if (needed_size + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // 如果缓冲区不够大，可以选择处理溢出，以下是示例处理
        strncpy(buffer, "缓冲区大小不足！", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // 确保字符串以 null 结尾
    }
}