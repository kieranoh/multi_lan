#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 提供されたターゲットURL文字列が指定されたドメイン内にあるか確認します。
もしそうであれば、リダイレクト用のターゲットURLを返します。そうでなければ、リダイレクト用にドメインURLにフォールバックします。
httpsプロトコルを使用します。

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: ターゲットURL文字列。
@param domain: プロトコルなしのドメイン文字列。

@return リダイレクト用のURL文字列。 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 入力のNULLチェック
    if (target == NULL || domain == NULL) {
        char* fallback = (char*)malloc(14 + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // ターゲットが"https://"で始まるか確認
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://で始まらない場合はドメインURLを返す
        char* fallback = (char*)malloc(14 + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // ターゲットのホスト部分を抽出
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }
    
    // ホスト名がドメインで終わるか確認
    size_t domain_len = strlen(domain);
    
    if (host_len >= domain_len) {
        const char* host_domain_part = host_start + (host_len - domain_len);
        
        // 完全一致またはサブドメインか確認
        if (strcmp(host_domain_part, domain) == 0) {
            // サブドメインかどうか確認（例: music.example.com）
            if (host_len == domain_len || 
                (host_len > domain_len && *(host_domain_part - 1) == '.')) {
                // ターゲットURLをそのまま返す
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) return NULL;
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // ドメインに一致しない場合はドメインURLを返す
    char* fallback = (char*)malloc(14 + strlen(domain) + 1);
    if (fallback == NULL) return NULL;
    sprintf(fallback, "https://%s", domain);
    return fallback;
}