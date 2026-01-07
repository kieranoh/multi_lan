#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief 대상 URL이 주어진 도메인 내에 있는지 확인하고 적절한 리디렉션 URL을 반환합니다.
 * 
 * @param target 대상 URL 문자열
 * @param domain 프로토콜을 제외한 도메인 문자열
 * @return char* 리디렉션을 위한 URL 문자열 (메모리 해제 필요)
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(20);
        if (default_url != NULL) {
            strcpy(default_url, "https://");
            strcat(default_url, domain);
        }
        return default_url;
    }
    
    // "https://" 접두사 확인 및 제거
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // 대상 URL이 https://로 시작하지 않는 경우 도메인으로 리디렉션
    if (strncmp(target, https_prefix, https_len) != 0) {
        char* result = (char*)malloc(strlen(domain) + https_len + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, https_prefix);
        strcat(result, domain);
        return result;
    }
    
    // https:// 이후의 부분 추출
    const char* target_without_protocol = target + https_len;
    
    // 도메인 끝 위치 찾기 (첫 번째 '/' 또는 문자열 끝)
    const char* target_domain_end = target_without_protocol;
    while (*target_domain_end != '\0' && *target_domain_end != '/' && *target_domain_end != ':') {
        target_domain_end++;
    }
    
    // 대상 도메인 추출
    size_t target_domain_len = target_domain_end - target_without_protocol;
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        return NULL;
    }
    strncpy(target_domain, target_without_protocol, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // 도메인 비교
    int is_same_domain = 0;
    
    // 정확히 일치하는 경우
    if (strcmp(target_domain, domain) == 0) {
        is_same_domain = 1;
    } else {
        // 서브도메인인 경우 확인 (예: music.example.com vs example.com)
        size_t domain_len = strlen(domain);
        size_t target_domain_str_len = strlen(target_domain);
        
        // 대상 도메인이 도메인으로 끝나고, 그 앞에 '.'이 있거나 전체 도메인이 같은 경우
        if (target_domain_str_len > domain_len + 1) {
            // 대상 도메인이 도메인으로 끝나는지 확인
            if (strcmp(target_domain + target_domain_str_len - domain_len, domain) == 0) {
                // 도메인 바로 앞이 '.'인지 확인
                if (target_domain[target_domain_str_len - domain_len - 1] == '.') {
                    is_same_domain = 1;
                }
            }
        }
    }
    
    free(target_domain);
    
    // 결과 생성
    if (is_same_domain) {
        // 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result != NULL) {
            strcpy(result, target);
        }
        return result;
    } else {
        // 도메인 URL로 리디렉션
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
}