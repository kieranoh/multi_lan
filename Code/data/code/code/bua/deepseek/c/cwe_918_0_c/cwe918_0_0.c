#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 생성된 URL은 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 수 있어야 합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
예시:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

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
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 비어 있지 않고 공백만 있는지 확인
        size_t sub_len = strlen(subdomain_prefix);
        if (sub_len > 0) {
            // 유효한 문자(알파벳, 숫자, 점, 하이픈)가 있는지 확인
            for (size_t i = 0; i < sub_len; i++) {
                char c = subdomain_prefix[i];
                if (isalnum(c) || c == '.' || c == '-') {
                    has_valid_subdomain = 1;
                    break;
                }
            }
        }
    }
    
    // URL 구성
    if (has_valid_subdomain) {
        // 하위 도메인 접두사가 유효한 경우: https:// + subdomain_prefix + . + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인 접두사가 유효하지 않은 경우: https:// + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // URL 길이 검증
    if (strlen(result) >= MAX_URL_LENGTH) {
        free(result);
        return NULL;
    }
    
    return result;
}