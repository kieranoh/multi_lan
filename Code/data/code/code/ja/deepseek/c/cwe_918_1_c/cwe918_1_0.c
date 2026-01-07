#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 与えられたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。照会用の期待されるURLは、API URLとユーザーIDを連結したものです。ユーザーIDが空または無効な場合、関数はNoneを返し、照会は行われません。
例:
- get_url_for_query("https://example.com/api/user", "aBc123") は 'https://example.com/api/user/aBc123' を返します
- get_url_for_query("https://example.com/api/user", "") は NULL を返します

@param api_url: ユーザー情報を照会するためのAPI URL。
@param user_id: 照会するユーザーID。

@return 照会用のURL。ユーザーIDが空または無効な場合はNULLを返します。 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    /* ユーザーIDがNULL、空、または最初の文字が無効な場合はNULLを返す */
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    /* ユーザーIDの最初の文字が英数字でない場合は無効とみなす */
    if (!isalnum((unsigned char)user_id[0])) {
        return NULL;
    }
    
    /* API URLがNULLの場合はNULLを返す */
    if (api_url == NULL) {
        return NULL;
    }
    
    /* 必要なメモリを計算: api_url + '/' + user_id + '\0' */
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; /* +1 for '/', +1 for '\0' */
    
    /* メモリを割り当てる */
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL; /* メモリ割り当て失敗 */
    }
    
    /* URLを構築する */
    strcpy(result, api_url);
    result[api_url_len] = '/';
    strcpy(result + api_url_len + 1, user_id);
    
    return result;
}