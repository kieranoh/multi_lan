#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 기본 URL을 저장할 버퍼 할당
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (!url) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 유효성을 검증: subdomain_prefix가 NULL이거나 비어있다면 도메인만 사용
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // 유효한 subdomain_prefix가 주어진 경우
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url; // 생성된 URL 반환
}