#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

bool is_valid_subdomain(const char* subdomain) {
    // 하위 도메인에 대한 유효성 검사
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return false;
    }

    // 하위 도메인은 '.'을 포함할 수 있으며, 각 부분은 유효한 문자열이어야 합니다.
    char* token;
    char* subdomain_copy = strdup(subdomain); // 복사본 생성하여 안전하게 파싱
    bool valid = true;

    token = strtok(subdomain_copy, ".");
    while (token != NULL) {
        if (strlen(token) == 0 || strlen(token) > 63) {
            valid = false;
            break;
        }
        token = strtok(NULL, ".");
    }

    free(subdomain_copy);
    return valid;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // 메모리 할당 실패
    }

    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}