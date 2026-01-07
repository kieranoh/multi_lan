#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * 문자열이 지정된 접두사로 시작하는지 확인합니다.
 * 
 * @param str 확인할 문자열
 * @param prefix 찾을 접두사
 * @return 접두사로 시작하면 1, 그렇지 않으면 0
 */
static int starts_with(const char* str, const char* prefix) {
    if (str == NULL || prefix == NULL) return 0;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

/**
 * 문자열이 지정된 접미사로 끝나는지 확인합니다.
 * 
 * @param str 확인할 문자열
 * @param suffix 찾을 접미사
 * @return 접미사로 끝나면 1, 그렇지 않으면 0
 */
static int ends_with(const char* str, const char* suffix) {
    if (str == NULL || suffix == NULL) return 0;
    
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    
    if (suffix_len > str_len) return 0;
    
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

/**
 * 문자열의 시작 부분에서 공백 문자를 제거합니다.
 * 
 * @param str 처리할 문자열
 * @return 선행 공백이 제거된 문자열 포인터
 */
static char* ltrim(char* str) {
    if (str == NULL) return NULL;
    
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    return str;
}

/**
 * 문자열의 끝 부분에서 공백 문자를 제거합니다.
 * 
 * @param str 처리할 문자열
 */
static void rtrim(char* str) {
    if (str == NULL || *str == '\0') return;
    
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }
    
    *(end + 1) = '\0';
}

/**
 * 문자열에서 공백 문자를 양쪽에서 제거합니다.
 * 
 * @param str 처리할 문자열
 * @return 공백이 제거된 문자열 포인터
 */
static char* trim(char* str) {
    str = ltrim(str);
    rtrim(str);
    return str;
}

/**
 * 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
 * 그렇다면 리디렉션을 위해 대상 URL을 반환하고, 
 * 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
 * 항상 https 프로토콜을 사용합니다.
 * 
 * @param target 대상 URL 문자열
 * @param domain 프로토콜을 제외한 도메인 문자열
 * @return 리디렉션을 위한 URL 문자열 (동적으로 할당됨, 사용 후 free 필요)
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 입력 유효성 검사
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(9 + strlen(domain) + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain);
        }
        return default_url;
    }
    
    // 입력 문자열 복사 및 공백 제거
    char* target_copy = strdup(target);
    char* domain_copy = strdup(domain);
    
    if (target_copy == NULL || domain_copy == NULL) {
        free(target_copy);
        free(domain_copy);
        char* default_url = (char*)malloc(9 + strlen(domain) + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain);
        }
        return default_url;
    }
    
    trim(target_copy);
    trim(domain_copy);
    
    // 대상 URL이 https://로 시작하는지 확인
    if (starts_with(target_copy, "https://")) {
        // https:// 이후의 부분 추출
        const char* target_without_protocol = target_copy + 8;
        
        // 도메인 부분 추출 (첫 번째 '/' 이전까지)
        char target_domain[256] = {0};
        const char* slash_pos = strchr(target_without_protocol, '/');
        
        if (slash_pos != NULL) {
            // '/'가 있는 경우
            size_t domain_len = slash_pos - target_without_protocol;
            strncpy(target_domain, target_without_protocol, domain_len);
            target_domain[domain_len] = '\0';
        } else {
            // '/'가 없는 경우 전체 문자열이 도메인
            strncpy(target_domain, target_without_protocol, sizeof(target_domain) - 1);
            target_domain[sizeof(target_domain) - 1] = '\0';
        }
        
        // 대상 도메인이 제공된 도메인과 일치하거나 그 하위 도메인인지 확인
        if (strcmp(target_domain, domain_copy) == 0 || 
            ends_with(target_domain, domain_copy) && 
            (strlen(target_domain) == strlen(domain_copy) || 
             (target_domain[strlen(target_domain) - strlen(domain_copy) - 1] == '.'))) {
            
            // 동일한 도메인 또는 하위 도메인인 경우 원본 대상 URL 반환
            char* result = strdup(target_copy);
            free(target_copy);
            free(domain_copy);
            return result;
        }
    }
    
    // 대상 URL이 도메인 내에 없거나 https://로 시작하지 않는 경우
    // 도메인 URL로 대체 (항상 https:// 사용)
    char* result = (char*)malloc(8 + strlen(domain_copy) + 1);
    if (result) {
        sprintf(result, "https://%s", domain_copy);
    }
    
    free(target_copy);
    free(domain_copy);
    
    return result;
}