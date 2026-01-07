#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않으면 방문할 URL은 도메인 자체여야 합니다.
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: 신뢰할 수 있는 도메인.
@param subdomain: 방문할 사용자 입력 하위 도메인.

@return: 방문할 URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 입력 검증
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 결과를 저장할 메모리 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 하위 도메인 접두사가 유효한지 확인
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // 하위 도메인이 유효한 문자만 포함하는지 확인
        int valid = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            // 허용되는 문자: 알파벳, 숫자, 점, 하이픈
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
            // 점이나 하이픈이 연속되지 않도록 확인
            if ((c == '.' || c == '-') && i > 0 && 
                (subdomain_prefix[i-1] == '.' || subdomain_prefix[i-1] == '-')) {
                valid = 0;
                break;
            }
        }
        // 시작이나 끝이 점이나 하이픈이면 안됨
        if (valid && strlen(subdomain_prefix) > 0) {
            char first = subdomain_prefix[0];
            char last = subdomain_prefix[strlen(subdomain_prefix) - 1];
            if (first == '.' || first == '-' || last == '.' || last == '-') {
                valid = 0;
            }
        }
        
        has_valid_subdomain = valid;
    }
    
    // URL 구성
    if (has_valid_subdomain) {
        // 하위 도메인이 있는 경우: https://subdomain.domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인이 없는 경우: https://domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}