#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、
   ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。 */
char* get_welcome_message(const char* username) {
    // メッセージのフォーマットを計算
    const char* format = "Welcome, %s!";
    size_t length = snprintf(NULL, 0, format, username); // 必要なバッファサイズを取得
    char* message = (char*)malloc(length + 1); // バッファを確保

    if (message != NULL) {
        snprintf(message, length + 1, format, username); // メッセージを生成
    }
    
    return message; // 生成されたメッセージを返す
}