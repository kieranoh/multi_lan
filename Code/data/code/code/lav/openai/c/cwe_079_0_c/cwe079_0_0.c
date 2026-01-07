#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    const char* template = "Welcome, %s!";
    // 計算メッセージの長さ
    size_t message_length = strlen(template) + strlen(username) - 2; // -2 to account for %s
    // メッセージ用のメモリを確保
    char* message = (char*)malloc(message_length + 1); // +1 for the null terminator
    if (message == NULL) {
        return NULL; // メモリの確保に失敗した場合
    }
    // メッセージの生成
    sprintf(message, template, username);
    return message;
}