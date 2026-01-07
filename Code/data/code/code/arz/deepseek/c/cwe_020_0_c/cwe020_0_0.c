#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 도메인 문자열을 정규화합니다 (선행/후행 공백 제거, 소문자 변환).
 * @param domain 정규화할 도메인 문자열
 * @return 정규화된 도메인 문자열 (동적으로 할당됨, 호출자가 해제해야 함)
 */
static char* normalize_domain(const char* domain) {
    if (!domain) return NULL;
    
    // 선행 공백 건너뛰기
    while (*domain && isspace((unsigned char)*domain)) {
        domain++;
    }
    
    // 도메인 길이 계산
    const char* end = domain;
    while (*end && !isspace((unsigned char)*end)) {
        end++;
    }
    
    size_t len = end - domain;
    if (len == 0) return NULL;
    
    // 메모리 할당 및 복사 (소문자로 변환)
    char* normalized = (char*)malloc(len + 1);
    if (!normalized) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        normalized[i] = tolower((unsigned char)domain[i]);
    }
    normalized[len] = '\0';
    
    return normalized;
}

/**
 * URL에서 호스트 부분을 추출합니다.
 * @param url URL 문자열
 * @return 호스트 문자열 (동적으로 할당됨, 호출자가 해제해야 함), 실패 시 NULL
 */
static char* extract_host_from_url(const char* url) {
    if (!url) return NULL;
    
    // "https://" 접두사 확인
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(url, https_prefix, https_len) != 0) {
        return NULL; // https 프로토콜이 아님
    }
    
    const char* host_start = url + https_len;
    if (*host_start == '\0') return NULL;
    
    // 호스트 끝 찾기 (포트나 경로 시작 전)
    const char* host_end = host_start;
    while (*host_end && *host_end != ':' && *host_end != '/' && *host_end != '?') {
        host_end++;
    }
    
    size_t host_len = host_end - host_start;
    if (host_len == 0) return NULL;
    
    // 호스트 부분 복사 (소문자로 변환)
    char* host = (char*)malloc(host_len + 1);
    if (!host) return NULL;
    
    for (size_t i = 0; i < host_len; i++) {
        host[i] = tolower((unsigned char)host_start[i]);
    }
    host[host_len] = '\0';
    
    return host;
}

/**
 * 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 도메인 URL로 리디렉션합니다.
 * https 프로토콜을 사용합니다.
 * 
 * @param target: 대상 URL 문자열.
 * @param domain: 프로토콜이 없는 도메인 문자열.
 * @return 리디렉션을 위한 URL 문자열 (동적으로 할당됨, 호출자가 해제해야 함).
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (!target || !domain) {
        char* default_redirect = (char*)malloc(20);
        if (default_redirect) {
            strcpy(default_redirect, "https://");
            strcat(default_redirect, domain ? domain : "");
            return default_redirect;
        }
        return NULL;
    }
    
    // 도메인 정규화
    char* normalized_domain = normalize_domain(domain);
    if (!normalized_domain) {
        char* default_redirect = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (default_redirect) {
            strcpy(default_redirect, "https://");
            strcat(default_redirect, domain);
            return default_redirect;
        }
        return NULL;
    }
    
    // 대상 URL에서 호스트 추출
    char* target_host = extract_host_from_url(target);
    
    // 대상 URL이 유효한 https URL이 아닌 경우 도메인으로 리디렉션
    if (!target_host) {
        free(normalized_domain);
        
        size_t redirect_len = strlen("https://") + strlen(normalized_domain) + 1;
        char* redirect_url = (char*)malloc(redirect_len);
        if (redirect_url) {
            strcpy(redirect_url, "https://");
            strcat(redirect_url, normalized_domain);
        }
        
        free(normalized_domain);
        return redirect_url;
    }
    
    // 도메인 내에 있는지 확인
    int is_within_domain = 0;
    
    // 정확히 일치하는 경우
    if (strcmp(target_host, normalized_domain) == 0) {
        is_within_domain = 1;
    } else {
        // 서브도메인인지 확인 (예: music.example.com이 example.com의 서브도메인인지)
        size_t domain_len = strlen(normalized_domain);
        size_t host_len = strlen(target_host);
        
        // 호스트가 도메인으로 끝나고, 바로 앞이 '.'인 경우
        if (host_len > domain_len + 1 && 
            target_host[host_len - domain_len - 1] == '.' &&
            strcmp(target_host + host_len - domain_len, normalized_domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    // 결과 생성
    char* result;
    if (is_within_domain) {
        // 대상 URL 반환 (원본 그대로)
        result = (char*)malloc(strlen(target) + 1);
        if (result) {
            strcpy(result, target);
        }
    } else {
        // 도메인 URL로 리디렉션
        size_t redirect_len = strlen("https://") + strlen(normalized_domain) + 1;
        result = (char*)malloc(redirect_len);
        if (result) {
            strcpy(result, "https://");
            strcat(result, normalized_domain);
        }
    }
    
    // 정리
    free(target_host);
    free(normalized_domain);
    
    return result;
}