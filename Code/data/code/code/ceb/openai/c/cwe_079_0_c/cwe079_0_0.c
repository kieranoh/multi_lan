#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // メッセージの形式を定義
    const char* format = "Welcome, %s!";
    
    // ユーザー名の長さを取得
    size_t username_length = strlen(username);
    
    // 必要なバッファサイズを計算
    size_t message_length = strlen(format) + username_length - 2; // -2 for %s
    char* message = (char*)malloc(message_length + 1); // +1 for null terminator
    
    // エラーチェック: メモリ確保に失敗した場合
    if (message == NULL) {
        return NULL; // 失敗した場合、NULLを返す
    }
    
    // メッセージを生成
    sprintf(message, format, username);
    
    return message; // 生成されたメッセージを返す
}