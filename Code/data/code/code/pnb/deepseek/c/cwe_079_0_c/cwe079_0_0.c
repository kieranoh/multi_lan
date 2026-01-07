#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // 入力検証
    if (username == NULL) {
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    // 必要なメモリの計算: "Welcome, " + username + "!" + null終端文字
    size_t username_len = strlen(username);
    size_t prefix_len = strlen("Welcome, ");
    size_t suffix_len = strlen("!");
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // メモリの割り当て
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // 文字列の構築
    strcpy(welcome_message, "Welcome, ");
    strcat(welcome_message, username);
    strcat(welcome_message, "!");
    
    return welcome_message;
}