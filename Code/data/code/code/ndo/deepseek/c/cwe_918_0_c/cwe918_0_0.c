#include <stdio.h>
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
    /* 결과 URL을 저장할 메모리 할당 */
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    /* 도메인 유효성 검사 */
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(result, "https://");
        return result;
    }
    
    /* 하위 도메인 접두사 유효성 검사 */
    int use_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        /* 하위 도메인에 유효한 문자만 포함되어 있는지 확인 */
        int valid = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                valid = 0;
                break;
            }
        }
        
        /* 점으로 시작하거나 끝나지 않아야 하며 연속된 점이 없어야 함 */
        if (valid && subdomain_prefix[0] != '.' && 
            subdomain_prefix[strlen(subdomain_prefix) - 1] != '.' &&
            strstr(subdomain_prefix, "..") == NULL) {
            use_subdomain = 1;
        }
    }
    
    /* URL 구성 */
    if (use_subdomain) {
        /* 하위 도메인이 있는 경우: https:// + 하위 도메인 + . + 도메인 */
        int needed_length = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1;
        if (needed_length > MAX_URL_LENGTH) {
            /* 버퍼 오버플로우 방지 */
            if (result != NULL) {
                free(result);
            }
            result = (char*)malloc(needed_length * sizeof(char));
            if (result == NULL) {
                return NULL;
            }
        }
        
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", 
                subdomain_prefix, domain);
    } else {
        /* 하위 도메인이 없는 경우: https:// + 도메인 */
        int needed_length = 8 + strlen(domain) + 1;
        if (needed_length > MAX_URL_LENGTH) {
            if (result != NULL) {
                free(result);
            }
            result = (char*)malloc(needed_length * sizeof(char));
            if (result == NULL) {
                return NULL;
            }
        }
        
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}