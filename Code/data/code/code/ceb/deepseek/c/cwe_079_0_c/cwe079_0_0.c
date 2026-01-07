#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    // 固定部分の文字列長さを計算
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    
    // ユーザー名がNULLの場合は安全なデフォルト値を返す
    if (username == NULL) {
        char* default_message = malloc(10);
        if (default_message != NULL) {
            strcpy(default_message, "Welcome!");
        }
        return default_message;
    }
    
    // 必要なメモリサイズを計算: prefix + username + suffix + null終端文字
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // メモリを確保
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ確保失敗
    }
    
    // 文字列を構築
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}