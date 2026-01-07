#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 
 * 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 * 
 * @param target: 대상 URL 문자열입니다.
 * @param domain: 프로토콜을 제외한 도메인 문자열입니다.
 * @return 리디렉션을 위한 URL 문자열입니다. (동적으로 할당되므로 호출자가 해제해야 함)
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL || strlen(target) == 0 || strlen(domain) == 0) {
        char* default_url = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain);
        }
        return default_url;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    const size_t https_len = strlen(https_prefix);
    
    // 대상 URL이 https://로 시작하지 않으면 도메인 URL 반환
    if (strncmp(target, https_prefix, https_len) != 0) {
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result) {
            sprintf(result, "https://%s", domain);
        }
        return result;
    }
    
    // 대상 URL에서 프로토콜 부분을 제외한 호스트명 시작 위치 찾기
    const char* host_start = target + https_len;
    
    // 호스트명 끝 찾기 (포트나 경로 시작 전)
    const char* host_end = host_start;
    while (*host_end != '\0' && *host_end != ':' && *host_end != '/') {
        host_end++;
    }
    
    // 호스트명 길이 계산
    size_t host_len = host_end - host_start;
    
    // 호스트명이 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    // 호스트명이 도메인과 정확히 일치하거나 도메인으로 끝나는 서브도메인인지 확인
    int is_within_domain = 0;
    
    if (host_len == domain_len) {
        // 정확히 같은 경우
        if (strncmp(host_start, domain, host_len) == 0) {
            is_within_domain = 1;
        }
    } else if (host_len > domain_len) {
        // 서브도메인인 경우: 호스트명이 ".domain"으로 끝나는지 확인
        if (host_start[host_len - domain_len - 1] == '.') {
            if (strncmp(host_start + host_len - domain_len, domain, domain_len) == 0) {
                is_within_domain = 1;
            }
        }
    }
    
    // 결과 생성
    if (is_within_domain) {
        // 대상 URL이 도메인 내에 있으면 그대로 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result) {
            strcpy(result, target);
        }
        return result;
    } else {
        // 대상 URL이 도메인 내에 없으면 도메인 URL 반환
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result) {
            sprintf(result, "https://%s", domain);
        }
        return result;
    }
}