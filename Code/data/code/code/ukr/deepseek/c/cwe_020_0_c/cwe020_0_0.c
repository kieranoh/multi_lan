#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
 * https 프로토콜을 사용합니다.
 * 
 * @param target: 대상 URL 문자열.
 * @param domain: 프로토콜이 없는 도메인 문자열.
 * @return 리디렉션을 위한 URL 문자열. 할당된 메모리는 호출자가 해제해야 합니다.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 검증
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8);
        if (default_result != NULL) {
            strcpy(default_result, "https://");
        }
        return default_result;
    }
    
    // target이 https://로 시작하는지 확인
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // https://로 시작하지 않으면 도메인 URL 반환
        char* result = (char*)malloc(strlen(domain) + https_len + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, https_prefix);
        strcat(result, domain);
        return result;
    }
    
    // target에서 도메인 부분 추출
    const char* target_domain_start = target + https_len;
    
    // 도메인 끝 찾기 (포트나 경로 시작 전)
    const char* target_domain_end = target_domain_start;
    while (*target_domain_end != '\0' && *target_domain_end != ':' && *target_domain_end != '/') {
        target_domain_end++;
    }
    
    size_t target_domain_len = target_domain_end - target_domain_start;
    
    // 도메인 비교
    int is_same_domain = 0;
    
    // 정확히 같은 도메인인 경우
    if (strlen(domain) == target_domain_len && 
        strncmp(target_domain_start, domain, target_domain_len) == 0) {
        is_same_domain = 1;
    }
    // 서브도메인인 경우 확인 (예: music.example.com은 example.com의 서브도메인)
    else if (target_domain_len > strlen(domain) + 1) {
        // 서브도메인 패턴 확인: *.domain
        size_t domain_len = strlen(domain);
        if (target_domain_len > domain_len + 1) {
            size_t offset = target_domain_len - domain_len - 1;
            if (target_domain_start[offset - 1] == '.' &&
                strncmp(target_domain_start + offset, domain, domain_len) == 0) {
                is_same_domain = 1;
            }
        }
    }
    
    if (is_same_domain) {
        // 같은 도메인 내에 있으면 원래 target 반환
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // 다른 도메인이면 도메인 URL 반환
        char* result = (char*)malloc(strlen(domain) + https_len + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, https_prefix);
        strcat(result, domain);
        return result;
    }
}