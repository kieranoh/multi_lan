#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージのベース部分
    const char* base_message = "Welcome, ";
    // メッセージ全体の長さを計算
    size_t message_length = strlen(base_message) + strlen(username) + 1; // +1 for null terminator

    // 新しいメッセージ用のメモリを確保
    char* message = (char*)malloc(message_length * sizeof(char));
    if (message == NULL) {
        return NULL; // メモリ確保に失敗した場合
    }

    // メッセージを作成
    strcpy(message, base_message);
    strcat(message, username);
    strcat(message, "!");

    return message; // 作成したメッセージを返す
}