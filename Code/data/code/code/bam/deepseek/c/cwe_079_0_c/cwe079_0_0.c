#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }
    
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    
    size_t username_len = strlen(username);
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL;
    }
    
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}