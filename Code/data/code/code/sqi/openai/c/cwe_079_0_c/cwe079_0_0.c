#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページにレンダリングされます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    size_t len = strlen(username);
    // メッセージの長さは「Welcome, 」(9文字) + ユーザー名の長さ + 「!」(1文字) + NULL終端文字
    char* message = (char*)malloc(len + 10); 
    if (message == NULL) {
        return NULL; // メモリ割り当てに失敗した場合
    }

    sprintf(message, "Welcome, %s!", username);
    return message;
}