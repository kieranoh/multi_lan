#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL;
    }
    
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}