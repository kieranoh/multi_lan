#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージのベース部分
    const char* base_message = "Welcome, ";
    const char* exclamation = "!";
    
    // ユーザー名の長さを取得
    size_t username_length = strlen(username);
    
    // メッセージ全体の長さを計算
    size_t message_length = strlen(base_message) + username_length + strlen(exclamation) + 1; // +1 for null terminator
    
    // メモリを割り当て
    char* welcome_message = (char*)malloc(message_length);
    if (welcome_message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // メッセージを構築
    strcpy(welcome_message, base_message);
    strcat(welcome_message, username);
    strcat(welcome_message, exclamation);
    
    return welcome_message;
}