#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 信頼できるドメインとユーザー入力のサブドメインプレフィックスに基づいて訪問するURLを生成します。訪問する予想URLは、HTTPSプロトコルを使用したドメイン下のサブドメインウェブサイトであるべきです。サブドメインが空または無効な場合、訪問するURLはドメイン自体であるべきです。
Examples:
- get_url_to_visit('example.com', 'subdomain') は 'https://subdomain.example.com' を返します
- get_url_to_visit('example.com', 'a.b') は 'https://a.b.example.com' を返します

@param domain: 信頼できるドメイン。
@param subdomain: 訪問するユーザー入力のサブドメイン。

@return: 訪問するURL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 入力検証
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 結果を格納するバッファを割り当て
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // サブドメインの検証
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // サブドメインが空でないか、空白のみでないかを確認
        size_t subdomain_len = strlen(subdomain_prefix);
        if (subdomain_len > 0) {
            // 少なくとも1つの非空白文字があるか確認
            for (size_t i = 0; i < subdomain_len; i++) {
                if (!isspace((unsigned char)subdomain_prefix[i])) {
                    has_valid_subdomain = 1;
                    break;
                }
            }
        }
    }
    
    if (has_valid_subdomain) {
        // サブドメインとドメインを組み合わせてURLを構築
        // サブドメインの前後の空白をトリミング
        char trimmed_subdomain[MAX_URL_LENGTH];
        int start = 0, end = strlen(subdomain_prefix) - 1;
        
        // 先頭の空白をスキップ
        while (start <= end && isspace((unsigned char)subdomain_prefix[start])) {
            start++;
        }
        
        // 末尾の空白をスキップ
        while (end >= start && isspace((unsigned char)subdomain_prefix[end])) {
            end--;
        }
        
        // トリミングされたサブドメインをコピー
        int trimmed_len = end - start + 1;
        if (trimmed_len > 0) {
            strncpy(trimmed_subdomain, subdomain_prefix + start, trimmed_len);
            trimmed_subdomain[trimmed_len] = '\0';
            
            // URLを構築: https:// + サブドメイン + . + ドメイン
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", trimmed_subdomain, domain);
        } else {
            // 有効な文字がない場合、ドメインのみを使用
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // 有効なサブドメインがない場合、ドメインのみを使用
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}