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
    // 결과를 저장할 버퍼 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 초기화
    result[0] = '\0';
    
    // 도메인 유효성 검사
    if (domain == NULL || domain[0] == '\0') {
        // 유효하지 않은 도메인인 경우 빈 문자열 반환
        return result;
    }
    
    // 하위 도메인 접두사 유효성 검사
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // 하위 도메인이 비어있지 않은지 확인
        // 선행/후행 공백 제거 및 유효성 검사
        int i = 0;
        int has_non_space = 0;
        while (subdomain_prefix[i] != '\0') {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                has_non_space = 1;
                break;
            }
            i++;
        }
        
        if (has_non_space) {
            has_valid_subdomain = 1;
        }
    }
    
    // URL 구성
    if (has_valid_subdomain) {
        // 하위 도메인이 있는 경우: https:// + subdomain_prefix + . + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인이 없는 경우: https:// + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}