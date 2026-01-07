#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜을 제외한 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(9);
        if (default_url != NULL) {
            strcpy(default_url, "https://");
            strcat(default_url, domain);
        }
        return default_url;
    }

    // https:// 프로토콜 확인
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

    // 대상 URL에서 호스트 부분 추출
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }

    // 호스트가 도메인으로 끝나는지 확인
    size_t domain_len = strlen(domain);
    
    if (host_len >= domain_len) {
        const char* host_domain_part = host_start + (host_len - domain_len);
        
        // 도메인이 정확히 일치하는지 또는 서브도메인인지 확인
        if ((host_len == domain_len && strcmp(host_start, domain) == 0) ||
            (host_len > domain_len && host_start[host_len - domain_len - 1] == '.' && 
             strcmp(host_domain_part, domain) == 0)) {
            // 대상 URL이 유효한 도메인 내에 있음
            char* result = (char*)malloc(strlen(target) + 1);
            if (result != NULL) {
                strcpy(result, target);
            }
            return result;
        }
    }

    // 대상 URL이 도메인 내에 없으면 도메인 URL 반환
    char* result = (char*)malloc(strlen(domain) + https_len + 1);
    if (result != NULL) {
        strcpy(result, https_prefix);
        strcat(result, domain);
    }
    return result;
}