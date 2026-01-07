#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    size_t username_length = strlen(username);
    const char* welcome_prefix = "Welcome, ";
    const char* welcome_suffix = "!";
    size_t message_length = strlen(welcome_prefix) + username_length + strlen(welcome_suffix) + 1;

    char* message = (char*)malloc(message_length);
    if (message == NULL) {
        return NULL; // 메모리 할당 실패시 NULL 반환
    }

    snprintf(message, message_length, "%s%s%s", welcome_prefix, username, welcome_suffix);
    return message;
}