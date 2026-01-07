#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // メモリを確保
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // メモリ確保に失敗
    }

    // サブドメインが有効かどうかをチェック
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // サブドメインを含めたURLを作成
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // サブドメインが無効なら、ドメイン自体のURLを作成
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}