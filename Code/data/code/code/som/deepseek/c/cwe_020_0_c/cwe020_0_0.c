#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 * 
 * @param target: 대상 URL 문자열입니다.
 * @param domain: 프로토콜이 없는 도메인 문자열입니다.
 * @return 리디렉션을 위한 URL 문자열입니다. 동적으로 할당되므로 호출자가 해제해야 합니다.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain ? domain : "example.com") + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain ? domain : "example.com");
        }
        return default_url;
    }

    // 1. 대상 URL에서 도메인 부분 추출
    const char* protocol_prefix = "https://";
    size_t protocol_len = strlen(protocol_prefix);
    
    // 대상 URL이 https://로 시작하는지 확인
    if (strncmp(target, protocol_prefix, protocol_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(protocol_len + strlen(domain) + 1);
        if (result) {
            sprintf(result, "%s%s", protocol_prefix, domain);
        }
        return result;
    }

    // https:// 이후의 부분 찾기
    const char* target_after_protocol = target + protocol_len;
    
    // 첫 번째 '/' 또는 문자열 끝까지가 도메인 부분
    const char* slash_pos = strchr(target_after_protocol, '/');
    size_t target_domain_len;
    
    if (slash_pos) {
        target_domain_len = slash_pos - target_after_protocol;
    } else {
        target_domain_len = strlen(target_after_protocol);
    }

    // 2. 대상 도메인이 제공된 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    // 대상 도메인이 제공된 도메인보다 짧으면 일치할 수 없음
    if (target_domain_len < domain_len) {
        char* result = (char*)malloc(protocol_len + strlen(domain) + 1);
        if (result) {
            sprintf(result, "%s%s", protocol_prefix, domain);
        }
        return result;
    }

    // 대상 도메인의 끝 부분이 제공된 도메인과 일치하는지 확인
    const char* target_domain_end = target_after_protocol + target_domain_len - domain_len;
    
    // 정확히 일치하거나, 도메인 바로 앞에 '.'이 있는 서브도메인인 경우
    int is_match = 0;
    
    if (strcmp(target_domain_end, domain) == 0) {
        // 정확히 일치하는 경우
        if (target_domain_len == domain_len) {
            is_match = 1;
        } 
        // 서브도메인인 경우: 도메인 앞에 '.'이 있어야 함
        else if (*(target_domain_end - 1) == '.') {
            is_match = 1;
        }
    }

    // 3. 결과 반환
    if (is_match) {
        // 대상 URL 반환 (복사본)
        char* result = (char*)malloc(strlen(target) + 1);
        if (result) {
            strcpy(result, target);
        }
        return result;
    } else {
        // 도메인 URL 반환
        char* result = (char*)malloc(protocol_len + strlen(domain) + 1);
        if (result) {
            sprintf(result, "%s%s", protocol_prefix, domain);
        }
        return result;
    }
}