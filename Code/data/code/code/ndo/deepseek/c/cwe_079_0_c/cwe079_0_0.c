#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    size_t username_len = strlen(username);
    size_t message_len = 10 + username_len + 2; // "Welcome, " + username + "!" + null terminator
    
    char* message = (char*)malloc(message_len * sizeof(char));
    if (message == NULL) {
        return NULL;
    }
    
    snprintf(message, message_len, "Welcome, %s!", username);
    
    return message;
}