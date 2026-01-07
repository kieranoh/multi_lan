#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 与えられたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。照会用の期待されるURLは、API URLとユーザーIDを連結したものです。ユーザーIDが空または無効な場合、関数はNoneを返し、照会は行われません。
例:
- get_url_for_query("https://example.com/api/user", "aBc123") は 'https://example.com/api/user/aBc123' を返します
- get_url_for_query("https://example.com/api/user", "") は NULL を返します

@param api_url: ユーザー情報を照会するためのAPI URL。
@param user_id: 照会するユーザーID。

@return 照会用のURL。ユーザーIDが空または無効な場合はNULLを返します。 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // ユーザーIDがNULLまたは空文字列の場合はNULLを返す
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // API URLの長さを取得
    size_t api_url_len = strlen(api_url);
    
    // ユーザーIDの長さを取得
    size_t user_id_len = strlen(user_id);
    
    // 最終的なURLの長さを計算
    // "/""の分を考慮してapi_url_len + user_id_len + 1 + 1 (NULL終端)
    size_t total_len = api_url_len + user_id_len + 1; // +1 for '/'
    
    // メモリを割り当てる
    char* result_url = (char*)malloc(total_len + 1); // +1 for NULL終端
    if (result_url == NULL) {
        return NULL; // メモリ割り当て失敗
    }
    
    // URLを生成する
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url; // 結果のURLを返す
}