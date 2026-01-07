#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 指定されたユーザー名を持つユーザーへの歓迎メッセージを生成します。このメッセージは、ユーザーがログインした後にHTMLページに表示されます。メッセージの形式は「ようこそ、<username>！」です。

@param username ユーザーのユーザー名。

@return さらなるレンダリングのための歓迎メッセージ。 */
char* get_welcome_message(const char* username) {
    // メッセージの形式を定義
    const char* message_format = "ようこそ、%s！";
    
    // ユーザー名の長さを取得
    size_t username_length = strlen(username);
    
    // メッセージの全体の長さを計算
    size_t message_length = strlen(message_format) + username_length - 2; // "%s"を2文字減らす

    // メッセージ用のメモリを確保
    char* message = (char*)malloc(message_length + 1); // +1はnull終端用

    // メッセージを生成
    sprintf(message, message_format, username);

    return message;
}