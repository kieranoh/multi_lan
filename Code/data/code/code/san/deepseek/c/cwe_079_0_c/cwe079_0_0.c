#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 指定されたユーザー名でユーザーのためのウェルカムメッセージを生成します。
 * このメッセージは、ユーザーがログインした後にHTMLページに表示されます。
 * メッセージの形式は「Welcome, <username>!」です。
 * 
 * @param username ユーザーのユーザー名。
 * @return さらなるレンダリングのためのウェルカムメッセージ。
 *         呼び出し元でfree()する必要があります。
 *         エラー時にはNULLを返します。
 */
char* get_welcome_message(const char* username) {
    // 入力の検証
    if (username == NULL) {
        return NULL;
    }
    
    // ユーザー名の長さを取得
    size_t username_len = strlen(username);
    
    // 固定部分の文字列: "Welcome, " (9文字) + "!" (1文字) + ヌル終端 (1文字)
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    
    // 必要なメモリサイズを計算
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 for null terminator
    
    // メモリを割り当て
    char* welcome_message = (char*)malloc(total_len);
    if (welcome_message == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // メッセージを構築
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}