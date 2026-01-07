#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // メモリを確保してURLを保存するためのバッファを準備
    char* url = (char*)malloc(MAX_URL_LENGTH);
    
    // サブドメインが空または無効な場合、ドメインだけを使う
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // サブドメインが有効な場合、URLを構築する
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}