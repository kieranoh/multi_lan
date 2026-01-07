#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 为指定用户名的用户生成欢迎消息。此消息将在用户登录后呈现在 HTML 页面中。消息格式为 "欢迎，<username>！"。

@param username 用户的用户名。

@return 用于进一步渲染的欢迎消息。 */
char* get_welcome_message(const char* username) {
    // 检查输入参数是否有效
    if (username == NULL) {
        return NULL;
    }
    
    // 计算所需内存大小：前缀"欢迎，" + 用户名 + 后缀"！" + 空终止符
    const char* prefix = "欢迎，";
    const char* suffix = "！";
    
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // 分配内存
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // 内存分配失败
    }
    
    // 构建欢迎消息
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}