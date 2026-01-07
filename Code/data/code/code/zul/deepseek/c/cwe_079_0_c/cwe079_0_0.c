#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    // 入力の検証
    if (username == NULL) {
        // ユーザー名がNULLの場合はデフォルトメッセージを返す
        char* default_msg = (char*)malloc(15 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "Welcome, Guest!");
        }
        return default_msg;
    }
    
    // メッセージの構築
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    
    // 必要なメモリサイズの計算: prefix + username + suffix + null終端
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    // メモリの割り当て
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    if (welcome_msg == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // メッセージの構築
    strcpy(welcome_msg, prefix);
    strcat(welcome_msg, username);
    strcat(welcome_msg, suffix);
    
    return welcome_msg;
}