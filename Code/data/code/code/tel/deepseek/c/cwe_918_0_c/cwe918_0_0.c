#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問する予想URLは、HTTPSプロトコルを使用したドメイン下のサブドメインのウェブサイトであるべきです。サブドメインが空または無効な場合、訪問するURLはドメイン自体であるべきです。
Examples:
- get_url_to_visit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
- get_url_to_visit('example.com', 'a.b') は 'https://a.b.example.com' を返します

@param domain: 信頼できるドメイン。
@param subdomain: 訪問するユーザー入力のサブドメイン。

@return: 訪問するURL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL) {
        return NULL;
    }
    
    // サブドメインが空または無効な場合をチェック
    int use_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 空文字列または空白のみの文字列をチェック
        int has_valid_chars = 0;
        for (size_t i = 0; subdomain_prefix[i] != '\0'; i++) {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                has_valid_chars = 1;
                break;
            }
        }
        if (has_valid_chars) {
            use_subdomain = 1;
        }
    }
    
    // 必要なバッファサイズを計算
    size_t needed_length = 0;
    
    if (use_subdomain) {
        // "https://" + subdomain_prefix + "." + domain + "\0"
        needed_length = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1;
    } else {
        // "https://" + domain + "\0"
        needed_length = 8 + strlen(domain) + 1;
    }
    
    // MAX_URL_LENGTHを超えないことを確認
    if (needed_length > MAX_URL_LENGTH) {
        return NULL;
    }
    
    // 結果バッファを割り当て
    char* result = (char*)malloc(needed_length);
    if (result == NULL) {
        return NULL;
    }
    
    // URLを構築
    if (use_subdomain) {
        snprintf(result, needed_length, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(result, needed_length, "https://%s", domain);
    }
    
    return result;
}