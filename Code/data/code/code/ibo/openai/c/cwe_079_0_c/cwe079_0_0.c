#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    const char* template = "Welcome, %s!";
    size_t message_length = strlen(template) + strlen(username) - 2; // -2 for %s
    char* message = malloc(message_length + 1); // +1 for the null terminator

    if (message == NULL) {
        return NULL; // Memory allocation failed
    }

    sprintf(message, template, username);
    return message;
}