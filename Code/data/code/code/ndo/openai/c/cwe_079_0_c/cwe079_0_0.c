#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「Welcome, <username>!」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのためのウェルカムメッセージ。 */
char* get_welcome_message(const char* username) {
    // メッセージのフォーマット
    const char* format = "Welcome, %s!";
    
    // ユーザー名の長さを取得
    size_t username_length = strlen(username);
    
    // フォーマット文字列の長さを取得
    size_t message_length = strlen(format) + username_length - 2; // "%s"を含む
    
    // メッセージ用のメモリを確保
    char* message = (char*)malloc(message_length + 1); // +1はヌル終端のため
    
    if (message == NULL) {
        return NULL; // メモリ確保に失敗
    }

    // メッセージを生成
    sprintf(message, format, username);
    
    return message;
}