#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열.
@param domain: 프로토콜을 제외한 도메인 문자열.

@return 리디렉션을 위한 URL 문자열. */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        return NULL;
    }
    
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // 대상 URL이 https://로 시작하는지 확인
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // https:// 이후의 부분 추출
    const char* target_without_protocol = target + https_len;
    
    // 도메인 끝을 찾기 위해 '/' 또는 문자열 끝까지 탐색
    const char* target_domain_end = target_without_protocol;
    while (*target_domain_end != '\0' && *target_domain_end != '/') {
        target_domain_end++;
    }
    
    // 대상 도메인 길이 계산
    size_t target_domain_len = target_domain_end - target_without_protocol;
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    if (target_domain_len >= domain_len) {
        // 대상 도메인 끝 부분이 제공된 도메인과 일치하는지 확인
        const char* target_domain_suffix = target_without_protocol + (target_domain_len - domain_len);
        
        if (strcmp(target_domain_suffix, domain) == 0) {
            // 정확히 일치하는 경우
            // 추가 확인: 완전한 도메인 부분인지 확인 (예: "example.com"이 "anotherexample.com"의 끝과 일치하지 않도록)
            if (target_domain_len == domain_len || 
                *(target_domain_suffix - 1) == '.') {
                // 대상 URL 반환
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) {
                    return NULL;
                }
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // 도메인이 일치하지 않으면 도메인 URL 반환
    char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (result == NULL) {
        return NULL;
    }
    sprintf(result, "%s%s", https_prefix, domain);
    return result;
}