#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 기본적으로 최대 URL 길이 설정
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 하위 도메인이 유효한지 검사
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // 하위 도메인 URL 생성
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인이 비어 있거나 유효하지 않을 경우 도메인 자체 반환
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}