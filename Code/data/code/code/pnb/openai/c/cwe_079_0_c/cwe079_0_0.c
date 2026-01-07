#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // Calculate the length of the welcome message
    size_t username_length = strlen(username);
    const char* welcome_prefix = "Welcome, ";
    size_t message_length = strlen(welcome_prefix) + username_length + 1; // +1 for null terminator

    // Allocate memory for the welcome message
    char* message = (char*)malloc(message_length * sizeof(char));
    if (message == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Create the welcome message
    strcpy(message, welcome_prefix);
    strcat(message, username);

    return message; // Return the constructed welcome message
}