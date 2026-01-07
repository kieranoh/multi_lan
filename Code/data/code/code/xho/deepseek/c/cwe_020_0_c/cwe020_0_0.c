#include <string.h>
#include <stdlib.h>
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
@param domain: 프로토콜이 없는 도메인 문자열.

@return 리디렉션을 위한 URL 문자열. */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        return NULL;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
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
    
    // 호스트 이름 추출
    char* hostname = (char*)malloc(host_len + 1);
    if (hostname == NULL) {
        return NULL;
    }
    strncpy(hostname, host_start, host_len);
    hostname[host_len] = '\0';
    
    // 도메인이 호스트 이름의 끝 부분과 일치하는지 확인
    size_t domain_len = strlen(domain);
    int is_same_domain = 0;
    
    if (host_len == domain_len) {
        // 정확히 같은 경우
        if (strcmp(hostname, domain) == 0) {
            is_same_domain = 1;
        }
    } else if (host_len > domain_len) {
        // 호스트 이름이 더 긴 경우: 서브도메인 확인
        if (hostname[host_len - domain_len - 1] == '.') {
            if (strcmp(hostname + (host_len - domain_len), domain) == 0) {
                is_same_domain = 1;
            }
        }
    }
    
    free(hostname);
    
    if (is_same_domain) {
        // 같은 도메인인 경우 원본 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // 다른 도메인인 경우 도메인 URL 반환
        char* result = (char*)malloc(strlen(https_prefix) + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}