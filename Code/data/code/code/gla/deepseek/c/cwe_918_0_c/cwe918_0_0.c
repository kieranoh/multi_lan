#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 생성된 URL은 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 수 있어야 합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
Examples:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.

@param domain: 신뢰할 수 있는 도메인.
@param subdomain: 방문할 사용자 입력 하위 도메인.

@return: 방문할 URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 입력 유효성 검사
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // 결과를 저장할 메모리 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 하위 도메인 접두사가 비어 있거나 유효하지 않은 경우 도메인만 반환
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 하위 도메인 접두사 유효성 검사 (알파벳, 숫자, 점, 하이픈만 허용)
    int valid = 1;
    for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
        char c = subdomain_prefix[i];
        if (!isalnum(c) && c != '.' && c != '-') {
            valid = 0;
            break;
        }
        
        // 점이 연속되거나 처음/끝에 있는지 확인
        if (c == '.' && (i == 0 || subdomain_prefix[i+1] == '\0' || subdomain_prefix[i+1] == '.')) {
            valid = 0;
            break;
        }
        
        // 하이픈이 처음이나 끝에 있는지 확인
        if (c == '-' && (i == 0 || subdomain_prefix[i+1] == '\0')) {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 최종 URL 생성
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    
    // 생성된 URL이 최대 길이를 초과하지 않는지 확인
    if (strlen(result) >= MAX_URL_LENGTH) {
        // URL이 너무 길면 도메인만 반환
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}