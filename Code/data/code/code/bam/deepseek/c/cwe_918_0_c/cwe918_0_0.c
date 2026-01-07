#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 생성된 URL은 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않으면 방문할 URL은 도메인 자체여야 합니다.
Examples:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다

@param domain: 신뢰할 수 있는 도메인.
@param subdomain: 방문할 사용자 입력 하위 도메인.

@return: 방문할 URL. */
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
    
    // 하위 도메인 접두사가 비어 있거나 유효하지 않은 경우
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        // 도메인 자체로 URL 생성
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 하위 도메인 접두사가 유효한지 확인 (알파벳, 숫자, 점, 하이픈만 허용)
    int valid = 1;
    for (size_t i = 0; subdomain_prefix[i] != '\0'; i++) {
        char c = subdomain_prefix[i];
        if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
            valid = 0;
            break;
        }
    }
    
    // 하위 도메인이 유효하지 않으면 도메인 자체로 URL 생성
    if (!valid) {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 하위 도메인 접두사가 점으로 시작하거나 끝나지 않는지 확인
    size_t len = strlen(subdomain_prefix);
    if (subdomain_prefix[0] == '.' || subdomain_prefix[len - 1] == '.') {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 연속된 점이 없는지 확인
    int consecutive_dots = 0;
    for (size_t i = 0; subdomain_prefix[i] != '\0'; i++) {
        if (subdomain_prefix[i] == '.') {
            if (consecutive_dots) {
                snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
                return result;
            }
            consecutive_dots = 1;
        } else {
            consecutive_dots = 0;
        }
    }
    
    // 최종 URL 생성
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    
    // 생성된 URL이 최대 길이를 초과하지 않는지 확인
    if (strlen(result) >= MAX_URL_LENGTH) {
        free(result);
        return NULL;
    }
    
    return result;
}