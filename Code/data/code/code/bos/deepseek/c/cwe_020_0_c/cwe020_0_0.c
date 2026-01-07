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
    // 입력 유효성 검사
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8 + strlen("https://") + 1);
        if (default_result != NULL) {
            strcpy(default_result, "https://");
        }
        return default_result;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    const size_t https_prefix_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_prefix_len) != 0) {
        // 대상이 https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_prefix_len + strlen(domain) + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
    
    // 대상 URL에서 프로토콜 부분을 제외한 호스트명 시작 위치 찾기
    const char* target_host_start = target + https_prefix_len;
    
    // 호스트명 끝 위치 찾기 (첫 번째 '/' 또는 문자열 끝)
    const char* host_end = target_host_start;
    while (*host_end != '\0' && *host_end != '/' && *host_end != ':') {
        host_end++;
    }
    
    // 호스트명 길이 계산
    size_t host_len = host_end - target_host_start;
    
    // 도메인 길이
    size_t domain_len = strlen(domain);
    
    // 호스트명이 도메인으로 끝나는지 확인
    int is_within_domain = 0;
    
    if (host_len >= domain_len) {
        // 호스트명의 끝이 도메인과 일치하는지 확인
        const char* host_suffix = target_host_start + (host_len - domain_len);
        
        if (strcmp(host_suffix, domain) == 0) {
            // 정확히 일치하는 경우
            is_within_domain = 1;
        } else if (host_len > domain_len) {
            // 호스트명이 더 길면 서브도메인일 수 있음
            // 도메인 바로 앞 문자가 '.'인지 확인
            if (*(host_suffix - 1) == '.') {
                // 서브도메인과 도메인이 일치하는지 확인
                if (strcmp(host_suffix, domain) == 0) {
                    is_within_domain = 1;
                }
            }
        }
    }
    
    if (is_within_domain) {
        // 대상 URL이 도메인 내에 있으면 원본 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result != NULL) {
            strcpy(result, target);
        }
        return result;
    } else {
        // 대상 URL이 도메인 내에 없으면 도메인 URL 반환
        char* result = (char*)malloc(https_prefix_len + domain_len + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
}