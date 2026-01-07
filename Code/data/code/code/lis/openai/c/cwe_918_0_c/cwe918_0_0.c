#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // URL을 저장할 메모리 할당
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 유효하지 않은 하위 도메인 처리
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // 하위 도메인이 유효할 경우
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url;
}