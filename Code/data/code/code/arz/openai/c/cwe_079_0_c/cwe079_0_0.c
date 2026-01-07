#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージの基本部分
    const char* message_prefix = "Welcome, ";
    const char* message_suffix = "!";
    
    // ユーザー名の長さを取得
    size_t username_length = strlen(username);
    size_t prefix_length = strlen(message_prefix);
    size_t suffix_length = strlen(message_suffix);
    
    // メッセージ全体の長さを計算
    size_t total_length = prefix_length + username_length + suffix_length + 1; // +1 for null terminator
    
    // メッセージ用のメモリを割り当て
    char* message = (char*)malloc(total_length);
    if (message == NULL) {
        return NULL; // メモリ割り当てに失敗した場合
    }
    
    // メッセージを構築
    strcpy(message, message_prefix); // 元のメッセージのプレフィックスをコピー
    strcat(message, username);        // ユーザー名を追加
    strcat(message, message_suffix);  // サフィックスを追加
    
    return message; // 生成したメッセージを返す
}