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
    
    // 대상 URL이 https://로 시작하는지 확인
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }

    // https:// 이후의 부분 추출
    const char* target_without_protocol = target + https_len;
    
    // 도메인 길이 계산
    size_t domain_len = strlen(domain);
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    size_t target_len = strlen(target_without_protocol);
    
    if (target_len >= domain_len) {
        // 대상 도메인이 정확히 제공된 도메인과 일치하는 경우
        if (strcmp(target_without_protocol, domain) == 0) {
            return strdup(target);
        }
        
        // 대상 도메인이 제공된 도메인으로 끝나고 그 앞이 '.'인 경우
        const char* domain_start = target_without_protocol + (target_len - domain_len);
        if (strcmp(domain_start, domain) == 0) {
            // 도메인 바로 앞이 '.'인지 확인 (서브도메인인 경우)
            if (domain_start > target_without_protocol && *(domain_start - 1) == '.') {
                return strdup(target);
            }
        }
    }

    // 도메인 내에 없으므로 도메인 URL 반환
    char* result = (char*)malloc(https_len + domain_len + 1);
    if (result == NULL) {
        return NULL;
    }
    sprintf(result, "%s%s", https_prefix, domain);
    return result;
}