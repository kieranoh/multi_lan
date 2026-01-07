#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜을 제외한 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8);
        if (default_result != NULL) {
            strcpy(default_result, "https://");
        }
        return default_result;
    }
    
    // "https://" 접두사 확인
    const char* https_prefix = "https://";
    const size_t prefix_len = 8; // strlen("https://")
    
    // 대상 URL이 "https://"로 시작하지 않는 경우
    if (strncmp(target, https_prefix, prefix_len) != 0) {
        // 도메인 URL 생성
        size_t result_len = prefix_len + strlen(domain) + 1;
        char* result = (char*)malloc(result_len);
        if (result == NULL) {
            return NULL;
        }
        snprintf(result, result_len, "%s%s", https_prefix, domain);
        return result;
    }
    
    // "https://" 이후의 부분 추출
    const char* target_after_prefix = target + prefix_len;
    
    // 도메인 끝을 찾기 위해 '/' 또는 문자열 끝까지 탐색
    const char* target_domain_end = target_after_prefix;
    while (*target_domain_end != '\0' && *target_domain_end != '/') {
        target_domain_end++;
    }
    
    // 대상 도메인 길이 계산
    size_t target_domain_len = target_domain_end - target_after_prefix;
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    // 대상 도메인이 제공된 도메인과 같거나 하위 도메인인 경우
    if (target_domain_len >= domain_len) {
        // 대상 도메인의 끝 부분이 제공된 도메인과 일치하는지 확인
        const char* target_domain_suffix = target_after_prefix + (target_domain_len - domain_len);
        
        // 정확히 일치하거나 하위 도메인인 경우 (예: music.example.com에서 .example.com)
        if ((target_domain_len == domain_len && strncmp(target_after_prefix, domain, domain_len) == 0) ||
            (target_domain_len > domain_len && target_after_prefix[target_domain_len - domain_len - 1] == '.' && 
             strncmp(target_domain_suffix, domain, domain_len) == 0)) {
            
            // 원본 대상 URL 복사하여 반환
            char* result = (char*)malloc(strlen(target) + 1);
            if (result == NULL) {
                return NULL;
            }
            strcpy(result, target);
            return result;
        }
    }
    
    // 도메인이 일치하지 않는 경우 도메인 URL 생성
    size_t result_len = prefix_len + strlen(domain) + 1;
    char* result = (char*)malloc(result_len);
    if (result == NULL) {
        return NULL;
    }
    snprintf(result, result_len, "%s%s", https_prefix, domain);
    return result;
}