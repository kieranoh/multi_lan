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
 * @param target: 대상 URL 문자열.
 * @param domain: 프로토콜을 제외한 도메인 문자열.
 * @return 리디렉션을 위한 URL 문자열.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain) + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
    
    // "https://" 접두사 확인
    const char* https_prefix = "https://";
    const size_t https_len = 8; // "https://" 길이
    
    // 대상 URL이 "https://"로 시작하는지 확인
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // 대상 URL에서 도메인 부분 추출
    const char* target_domain_start = target + https_len;
    
    // 도메인 끝 위치 찾기 (첫 번째 '/' 또는 문자열 끝)
    const char* slash_pos = strchr(target_domain_start, '/');
    size_t target_domain_len;
    
    if (slash_pos != NULL) {
        target_domain_len = slash_pos - target_domain_start;
    } else {
        target_domain_len = strlen(target_domain_start);
    }
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    // 대상 도메인이 제공된 도메인보다 짧으면 도메인 URL 반환
    if (target_domain_len < domain_len) {
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    const char* target_domain_end = target_domain_start + target_domain_len;
    const char* domain_match_start = target_domain_end - domain_len;
    
    // 도메인이 정확히 일치하는지 확인
    if (strcmp(domain_match_start, domain) == 0) {
        // 도메인이 정확히 일치하면 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    }
    
    // 서브도메인인 경우 확인 (예: music.example.com)
    if (target_domain_len > domain_len && 
        *(domain_match_start - 1) == '.' &&
        strcmp(domain_match_start, domain) == 0) {
        // 서브도메인이면 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    }
    
    // 도메인이 일치하지 않으면 도메인 URL 반환
    char* result = (char*)malloc(https_len + strlen(domain) + 1);
    if (result == NULL) return NULL;
    sprintf(result, "%s%s", https_prefix, domain);
    return result;
}