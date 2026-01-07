#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問するURLは、HTTPSプロトコルを使用したドメインの下のサブドメインウェブサイトである必要があります。サブドメインが空または無効な場合、訪問するURLはドメイン自体である必要があります。
例:
- get_url_to_visit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
- get_url_to_visit('example.com', 'a.b') は 'https://a.b.example.com' を返します

@param domain: 信頼できるドメイン。
@param subdomain: 訪問するユーザー入力のサブドメイン。

@return: 訪問するURL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 入力検証
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // 結果を格納するバッファを確保
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // サブドメインの検証
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // サブドメインが有効な文字のみを含むかチェック
        int i;
        for (i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
                break;
            }
        }
        has_valid_subdomain = (subdomain_prefix[i] == '\0' && i > 0);
    }
    
    // URLを構築
    if (has_valid_subdomain) {
        // サブドメインとドメインを組み合わせる
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // ドメインのみ
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // 結果の長さを確認
    if (strlen(result) >= MAX_URL_LENGTH) {
        free(result);
        return NULL;
    }
    
    return result;
}