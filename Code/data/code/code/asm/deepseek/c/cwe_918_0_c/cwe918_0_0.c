#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않으면 방문할 URL은 도메인 자체여야 합니다.
예시:
- get_url_to_visit('example.com', 'subdomain')은 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')은 'https://a.b.example.com'을 반환합니다.

@param domain: 신뢰할 수 있는 도메인.
@param subdomain: 방문할 사용자 입력 하위 도메인.

@return: 방문할 URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 입력 검증
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 결과를 저장할 버퍼 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 하위 도메인 접두사가 유효한지 확인
    int use_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // 하위 도메인 접두사가 유효한 문자로만 구성되어 있는지 확인
        int valid = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                valid = 0;
                break;
            }
        }
        use_subdomain = valid;
    }
    
    // URL 구성
    if (use_subdomain) {
        // 하위 도메인이 있는 경우: https:// + subdomain_prefix + . + domain
        int needed_length = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1; // "https://" + subdomain + "." + domain + "\0"
        if (needed_length > MAX_URL_LENGTH) {
            free(result);
            return NULL;
        }
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인이 없는 경우: https:// + domain
        int needed_length = 8 + strlen(domain) + 1; // "https://" + domain + "\0"
        if (needed_length > MAX_URL_LENGTH) {
            free(result);
            return NULL;
        }
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}