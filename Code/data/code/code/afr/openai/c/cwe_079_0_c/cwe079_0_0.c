#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージの長さを計算
    size_t username_length = strlen(username);
    const char* template = "Welcome, ";
    const char* suffix = "!";
    size_t message_length = strlen(template) + username_length + strlen(suffix) + 1; // +1 for null terminator

    // メモリを割り当てる
    char* message = (char*)malloc(message_length);
    if (message == NULL) {
        return NULL; // メモリ割り当て失敗
    }

    // メッセージを形成
    strcpy(message, template);
    strcat(message, username);
    strcat(message, suffix);

    return message;
}