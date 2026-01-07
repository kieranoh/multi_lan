#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    const char* template = "Welcome, %s!";
    int length = snprintf(NULL, 0, template, username);
    char* message = (char*)malloc(length + 1);
    if (message != NULL) {
        sprintf(message, template, username);
    }
    return message;
}