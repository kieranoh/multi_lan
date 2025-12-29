#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위한 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위한 도메인 URL로 대체합니다.
https 프로토콜을 사용하세요.

예시:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜이 없는 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8 + strlen(domain) + 1);
        if (default_result == NULL) {
            return NULL;
        }
        sprintf(default_result, "https://%s", domain);
        return default_result;
    }

    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // 대상 URL이 "https://"로 시작하는지 확인
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인으로 리디렉션
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }

    // "https://" 이후의 부분 추출
    const char* target_after_https = target + https_len;
    
    // 도메인 끝을 찾기 위해 '/' 또는 문자열 끝까지 탐색
    const char* target_domain_end = target_after_https;
    while (*target_domain_end != '\0' && *target_domain_end != '/') {
        target_domain_end++;
    }
    
    // 대상 도메인 길이 계산
    size_t target_domain_len = target_domain_end - target_after_https;
    
    // 대상 도메인 추출
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        return NULL;
    }
    strncpy(target_domain, target_after_https, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // 도메인이 일치하는지 확인 (예: example.com이 music.example.com의 끝과 일치하는지)
    size_t domain_len = strlen(domain);
    size_t target_domain_actual_len = strlen(target_domain);
    
    int is_within_domain = 0;
    
    if (target_domain_actual_len == domain_len) {
        // 정확히 같은 도메인인 경우
        if (strcmp(target_domain, domain) == 0) {
            is_within_domain = 1;
        }
    } else if (target_domain_actual_len > domain_len) {
        // 하위 도메인인 경우: .example.com으로 끝나는지 확인
        if (target_domain[target_domain_actual_len - domain_len - 1] == '.' &&
            strcmp(target_domain + target_domain_actual_len - domain_len, domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    free(target_domain);
    
    if (is_within_domain) {
        // 원래 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // 도메인 URL로 대체
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}