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
    
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    size_t message_length = strlen(prefix) + strlen(username) + strlen(suffix) + 1; // +1 for null terminator

    char* welcome_message = (char*)malloc(message_length);
    if (welcome_message == NULL) {
        return NULL; // Memory allocation failed
    }

    snprintf(welcome_message, message_length, "%s%s%s", prefix, username, suffix);
    return welcome_message;
}