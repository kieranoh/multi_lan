#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 为指定用户名的用户生成欢迎消息。此消息将在用户登录后呈现在 HTML 页面中。消息格式为 "欢迎，<username>！"。
@param username 用户的用户名。
@return 用于进一步渲染的欢迎消息。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL; // 返回 NULL 以处理无效输入
    }

    // 计算欢迎消息的长度
    const char* greeting = "欢迎，";
    const char* suffix = "！";
    size_t message_length = strlen(greeting) + strlen(username) + strlen(suffix) + 1; // +1 for the null terminator

    // 分配内存以存储欢迎消息
    char* welcome_message = (char*)malloc(message_length);
    if (welcome_message == NULL) {
        return NULL; // 内存分配失败
    }

    // 生成欢迎消息
    snprintf(welcome_message, message_length, "%s%s%s", greeting, username, suffix);

    return welcome_message; // 返回生成的欢迎消息
}