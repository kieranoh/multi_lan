#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 기본 URL을 위한 메모리 할당
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 유효성을 검사하여 하위 도메인이 비어 있거나 유효하지 않은 경우
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0 || strchr(subdomain_prefix, '.') == NULL) {
        // 하위 도메인이 유효하지 않으면 도메인 자체를 사용
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // 유효한 하위 도메인인 경우
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url; // 생성된 URL 반환
}