#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // URL을 담을 메모리 할당
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 서브도메인 접두사가 유효한지 검사
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // 서브도메인이 비어 있거나 NULL이면 도메인만 반환
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // 유효한 서브도메인 접두사가 있는 경우
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }

    return url; // 생성된 URL 반환
}