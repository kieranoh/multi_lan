#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // ウェルカムメッセージのベース部分
    const char* base_message = "Welcome, ";
    
    // メッセージの長さを計算
    size_t message_length = strlen(base_message) + strlen(username) + 1; // +1 for null terminator

    // メモリを動的に割り当て
    char* welcome_message = (char*)malloc(message_length * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // メモリ割り当て失敗
    }

    // メッセージを生成
    strcpy(welcome_message, base_message);
    strcat(welcome_message, username);
    strcat(welcome_message, "!");

    return welcome_message;
}