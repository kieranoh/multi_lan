#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 * 
 * @param target: 대상 URL 문자열입니다.
 * @param domain: 프로토콜을 제외한 도메인 문자열입니다.
 * @return 리디렉션을 위한 URL 문자열입니다. 동적으로 할당되므로 사용 후 free() 해야 합니다.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain ? domain : "example.com") + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain ? domain : "example.com");
        return default_url;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    const char* https_prefix = "https://";
    const size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // 대상 URL에서 프로토콜 부분을 제외한 호스트명 시작 위치 찾기
    const char* host_start = target + https_len;
    
    // 호스트명 끝 찾기 (첫 번째 '/' 또는 문자열 끝)
    const char* host_end = host_start;
    while (*host_end != '\0' && *host_end != '/' && *host_end != ':') {
        host_end++;
    }
    
    // 호스트명 길이 계산
    size_t host_len = host_end - host_start;
    
    // 호스트명 추출
    char* hostname = (char*)malloc(host_len + 1);
    if (hostname == NULL) return NULL;
    strncpy(hostname, host_start, host_len);
    hostname[host_len] = '\0';
    
    // 도메인이 호스트명의 끝 부분과 일치하는지 확인
    size_t domain_len = strlen(domain);
    int is_within_domain = 0;
    
    if (host_len >= domain_len) {
        // 호스트명이 도메인과 정확히 일치하는 경우
        if (strcmp(hostname, domain) == 0) {
            is_within_domain = 1;
        }
        // 호스트명이 도메인으로 끝나는 서브도메인인 경우
        else if (host_len > domain_len && hostname[host_len - domain_len - 1] == '.') {
            if (strcmp(hostname + (host_len - domain_len), domain) == 0) {
                is_within_domain = 1;
            }
        }
    }
    
    free(hostname);
    
    // 결과 생성
    if (is_within_domain) {
        // 동일한 도메인 내에 있으면 원본 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // 다른 도메인이면 기본 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}