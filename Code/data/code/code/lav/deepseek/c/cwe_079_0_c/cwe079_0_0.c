#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    // 入力検証
    if (username == NULL) {
        char* default_message = malloc(11 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    // 必要なメモリの計算: "Welcome, " + username + "!" + null終端
    size_t welcome_len = strlen("Welcome, ");
    size_t username_len = strlen(username);
    size_t exclamation_len = strlen("!");
    size_t total_len = welcome_len + username_len + exclamation_len + 1;
    
    // メモリの割り当て
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // メッセージの構築
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}