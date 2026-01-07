#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // ユーザー名がNULLまたは空の場合のチェック
    if (username == NULL || strlen(username) == 0) {
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    // メッセージの長さを計算: "Welcome, " + username + "!" + null終端
    size_t welcome_len = strlen("Welcome, ");
    size_t username_len = strlen(username);
    size_t exclamation_len = strlen("!");
    size_t total_len = welcome_len + username_len + exclamation_len + 1;
    
    // メモリを動的に確保
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ確保失敗
    }
    
    // メッセージを構築
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}