#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(15);
        if (default_url != NULL) {
            strcpy(default_url, "https://example.com");
        }
        return default_url;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(strlen(domain) + https_len + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
    
    // 대상 URL에서 프로토콜 부분을 제외한 호스트명 추출
    const char* target_host = target + https_len;
    
    // 호스트명에서 포트나 경로가 있는 경우를 대비하여 첫 번째 '/' 또는 ':' 또는 문자열 끝까지 찾기
    const char* host_end = target_host;
    while (*host_end != '\0' && *host_end != '/' && *host_end != ':') {
        host_end++;
    }
    
    // 호스트명 길이 계산
    size_t host_len = host_end - target_host;
    
    // 호스트명이 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    // 호스트명이 도메인과 정확히 일치하거나 서브도메인인 경우 확인
    int is_within_domain = 0;
    
    if (host_len == domain_len) {
        // 정확히 같은 길이인 경우 완전 일치 확인
        if (strncmp(target_host, domain, host_len) == 0) {
            is_within_domain = 1;
        }
    } else if (host_len > domain_len) {
        // 호스트명이 더 긴 경우 서브도메인일 수 있음
        // 호스트명이 ".domain"으로 끝나는지 확인
        if (target_host[host_len - domain_len - 1] == '.') {
            if (strncmp(target_host + host_len - domain_len, domain, domain_len) == 0) {
                is_within_domain = 1;
            }
        }
    }
    
    if (is_within_domain) {
        // 도메인 내에 있으면 원래 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result != NULL) {
            strcpy(result, target);
        }
        return result;
    } else {
        // 도메인 내에 없으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
}