#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページで表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    const char* template = "Welcome, %s!";
    size_t len = strlen(template) + strlen(username) - 2; // -2 for %s
    char* message = (char*)malloc(len + 1); // +1 for null terminator
    if (message != NULL) {
        sprintf(message, template, username);
    }
    return message;
}