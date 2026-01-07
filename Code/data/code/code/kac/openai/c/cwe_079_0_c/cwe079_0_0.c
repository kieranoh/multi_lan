#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // メッセージの形式を定義する
    const char* message_format = "Welcome, %s!";
    // メッセージの長さを計算する
    int length = strlen(message_format) + strlen(username) - 2; // %sの長さを減算
    // メッセージ用のメモリを動的に割り当てる
    char* message = (char*)malloc(length + 1); // +1はヌル終端のため
    if (message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    // メッセージを生成する
    sprintf(message, message_format, username);
    return message; // 生成したメッセージを返す
}