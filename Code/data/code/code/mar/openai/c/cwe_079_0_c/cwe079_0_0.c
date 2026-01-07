#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージの長さを計算
    size_t username_length = strlen(username);
    size_t message_length = username_length + 10; // "Welcome, " (8) + "!" (1) + '\0' (1)
    
    // メモリを動的に割り当て
    char* message = (char*)malloc(message_length * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ割り当て失敗
    }

    // メッセージを生成
    sprintf(message, "Welcome, %s!", username);
    
    return message; // 生成したメッセージを返す
}