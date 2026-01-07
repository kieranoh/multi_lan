#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // ユーザー名がNULLまたは空の場合はデフォルトメッセージを返す
    if (username == NULL || strlen(username) == 0) {
        char* default_msg = (char*)malloc(11 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "Welcome, !");
        }
        return default_msg;
    }
    
    // メッセージの長さを計算: "Welcome, " + username + "!" + null終端
    size_t welcome_len = strlen("Welcome, ");
    size_t username_len = strlen(username);
    size_t total_len = welcome_len + username_len + 2; // +2 for '!' and null terminator
    
    // メモリを確保
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ確保に失敗
    }
    
    // メッセージを構築
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}