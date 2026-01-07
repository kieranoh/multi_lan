#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    // 固定部分の文字列長さ + ユーザー名の長さ + 終端文字
    const char* welcome_prefix = "Welcome, ";
    const char* welcome_suffix = "!";
    
    // 必要なメモリサイズを計算
    size_t prefix_len = strlen(welcome_prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(welcome_suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // メモリを確保
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ確保失敗
    }
    
    // 文字列を構築
    strcpy(message, welcome_prefix);
    strcat(message, username);
    strcat(message, welcome_suffix);
    
    return message;
}