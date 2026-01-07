#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 기본 URL 길이를 HTTPS와 도메인 길이로 설정
    const char* https_prefix = "https://";
    size_t domain_len = strlen(domain);
    size_t prefix_len = strlen(https_prefix);
    
    // 하위 도메인 접두사가 유효한지 확인
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // 하위 도메인이 비어있으면 도메인만 반환
        char* url = (char*)malloc(prefix_len + domain_len + 1); // +1 for null terminator
        if (url == NULL) {
            return NULL; // 메모리 할당 실패
        }
        sprintf(url, "%s%s", https_prefix, domain);
        return url;
    }

    // 하위 도메인과 도메인을 결합
    size_t subdomain_len = strlen(subdomain_prefix);
    char* url = (char*)malloc(prefix_len + subdomain_len + domain_len + 2); // +2 for '.' and null terminator
    if (url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // URL 생성
    sprintf(url, "%s%s.%s", https_prefix, subdomain_prefix, domain);
    return url;
}