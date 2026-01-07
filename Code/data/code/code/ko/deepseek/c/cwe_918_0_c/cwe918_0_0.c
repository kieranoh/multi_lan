#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 신뢰할 수 있는 도메인과 사용자 입력 서브도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 서브도메인 웹사이트여야 합니다. 서브도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
예시:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

@param domain: 신뢰할 수 있는 도메인입니다.
@param subdomain: 방문할 사용자 입력 서브도메인입니다.

@return: 방문할 URL입니다. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 입력 검증
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // 결과를 저장할 버퍼 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 서브도메인 접두사가 유효한지 확인
    int use_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // 서브도메인이 유효한 문자로만 구성되어 있는지 확인
        int valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            // 허용되는 문자: 알파벳, 숫자, 점, 하이픈
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
            // 점이 연속되지 않도록 확인
            if (c == '.' && i > 0 && subdomain_prefix[i-1] == '.') {
                valid = 0;
                break;
            }
        }
        // 시작이나 끝이 점이나 하이픈이 아닌지 확인
        if (valid && strlen(subdomain_prefix) > 0) {
            char first = subdomain_prefix[0];
            char last = subdomain_prefix[strlen(subdomain_prefix) - 1];
            if (first == '.' || first == '-' || last == '.' || last == '-') {
                valid = 0;
            }
        }
        
        use_subdomain = valid;
    }
    
    // URL 생성
    if (use_subdomain) {
        // 서브도메인이 있는 경우: https://서브도메인.도메인
        int needed_length = 8 + strlen("https://") + strlen(subdomain_prefix) + 1 + strlen(domain) + 1;
        if (needed_length > MAX_URL_LENGTH) {
            // 버퍼가 충분하지 않으면 도메인만 사용
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        } else {
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    } else {
        // 서브도메인이 없는 경우: https://도메인
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}