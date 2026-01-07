#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // 计算所需内存大小: "Welcome, " (9个字符) + username长度 + "!" (1个字符) + 空终止符 (1个字符)
    size_t welcome_len = strlen("Welcome, ");
    size_t username_len = strlen(username);
    size_t total_len = welcome_len + username_len + 2; // +2 用于 "!" 和空终止符
    
    // 分配内存
    char* message = (char*)malloc(total_len);
    if (message == NULL) {
        return NULL; // 内存分配失败
    }
    
    // 构建欢迎消息
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}