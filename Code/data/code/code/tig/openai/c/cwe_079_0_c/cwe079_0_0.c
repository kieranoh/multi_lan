#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }
    
    const char* welcome_prefix = "Welcome, ";
    const char* welcome_suffix = "!";
    
    size_t prefix_length = strlen(welcome_prefix);
    size_t username_length = strlen(username);
    size_t suffix_length = strlen(welcome_suffix);
    
    char* message = (char*)malloc(prefix_length + username_length + suffix_length + 1);
    if (message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    strcpy(message, welcome_prefix);
    strcat(message, username);
    strcat(message, welcome_suffix);
    
    return message;
}