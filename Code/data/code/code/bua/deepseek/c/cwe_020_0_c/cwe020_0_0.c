#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열.
@param domain: 프로토콜이 없는 도메인 문자열.

@return 리디렉션을 위한 URL 문자열. */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen("example.com") + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", "example.com");
        return default_url;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // 대상이 https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // 대상 URL에서 호스트 부분 추출
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }
    
    // 호스트가 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    bool is_within_domain = false;
    
    if (host_len >= domain_len) {
        const char* host_domain_part = host_start + (host_len - domain_len);
        
        // 도메인 부분이 정확히 일치하는지 확인
        if (strcmp(host_domain_part, domain) == 0) {
            // 도메인 바로 앞이 '.'이거나 전체 호스트가 도메인과 같은 경우
            if (host_len == domain_len || *(host_domain_part - 1) == '.') {
                is_within_domain = true;
            }
        }
    }
    
    if (is_within_domain) {
        // 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}