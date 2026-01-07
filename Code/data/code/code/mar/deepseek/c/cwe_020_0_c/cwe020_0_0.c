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
 * @return 리디렉션을 위한 URL 문자열입니다. 동적으로 할당되므로 호출자가 해제해야 합니다.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8 + strlen(domain) + 1);
        if (default_result == NULL) return NULL;
        sprintf(default_result, "https://%s", domain);
        return default_result;
    }
    
    // 대상 URL이 https://로 시작하는지 확인
    const char* https_prefix = "https://";
    const size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // https:// 이후의 부분 추출
    const char* target_without_protocol = target + https_len;
    
    // 도메인 길이 계산
    size_t domain_len = strlen(domain);
    
    // 대상 URL의 호스트 부분이 도메인으로 끝나는지 확인
    // 호스트 부분을 추출하기 위해 첫 번째 '/' 찾기
    const char* first_slash = strchr(target_without_protocol, '/');
    size_t host_len;
    
    if (first_slash == NULL) {
        // '/'가 없으면 전체 문자열이 호스트
        host_len = strlen(target_without_protocol);
    } else {
        host_len = first_slash - target_without_protocol;
    }
    
    // 호스트 부분이 도메인과 정확히 일치하거나 도메인으로 끝나는지 확인
    int is_within_domain = 0;
    
    if (host_len == domain_len) {
        // 호스트 길이가 도메인 길이와 같으면 정확히 일치하는지 확인
        if (strcmp(target_without_protocol, domain) == 0) {
            is_within_domain = 1;
        }
    } else if (host_len > domain_len) {
        // 호스트가 도메인보다 길면 서브도메인일 수 있음
        // 호스트가 ".domain"으로 끝나는지 확인
        if (target_without_protocol[host_len - domain_len - 1] == '.') {
            if (strcmp(target_without_protocol + (host_len - domain_len), domain) == 0) {
                is_within_domain = 1;
            }
        }
    }
    
    if (is_within_domain) {
        // 도메인 내에 있으면 원래 대상 URL 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // 도메인 내에 없으면 도메인 URL 반환
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
}