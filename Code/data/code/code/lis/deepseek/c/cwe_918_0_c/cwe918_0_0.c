#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않으면 방문할 URL은 도메인 자체여야 합니다.
Examples:
- get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다
- get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다

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
    
    // 하위 도메인 접두사가 비어 있거나 NULL인 경우 도메인만 사용
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 하위 도메인 접두사 유효성 검사
    int valid = 1;
    const char* ptr = subdomain_prefix;
    
    // 하위 도메인 접두사가 유효한 문자로만 구성되어 있는지 확인
    while (*ptr != '\0') {
        if (!isalnum((unsigned char)*ptr) && *ptr != '.' && *ptr != '-') {
            valid = 0;
            break;
        }
        ptr++;
    }
    
    // 하위 도메인 접두사가 유효하지 않거나 "."으로 시작하거나 끝나는 경우
    if (!valid || subdomain_prefix[0] == '.' || subdomain_prefix[strlen(subdomain_prefix) - 1] == '.') {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 연속된 마침표 확인
    ptr = subdomain_prefix;
    while (*ptr != '\0' && *(ptr + 1) != '\0') {
        if (*ptr == '.' && *(ptr + 1) == '.') {
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
            return result;
        }
        ptr++;
    }
    
    // 최종 URL 생성
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    
    // 생성된 URL이 최대 길이를 초과하지 않는지 확인
    if (strlen(result) >= MAX_URL_LENGTH) {
        // URL이 너무 길면 도메인만 사용
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}