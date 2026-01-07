#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/**
 * 하위 도메인 접두사가 유효한지 확인합니다.
 * 유효한 하위 도메인은 비어 있지 않아야 하며, 알파벳, 숫자, 점, 하이픈만 포함할 수 있습니다.
 * 점으로 시작하거나 끝나지 않아야 하며, 연속된 점을 포함하지 않아야 합니다.
 * 
 * @param subdomain 확인할 하위 도메인 문자열
 * @return 유효하면 1, 그렇지 않으면 0
 */
static int is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return 0;
    }
    
    int len = strlen(subdomain);
    
    // 점으로 시작하거나 끝나면 안 됨
    if (subdomain[0] == '.' || subdomain[len - 1] == '.') {
        return 0;
    }
    
    // 연속된 점 확인
    for (int i = 0; i < len - 1; i++) {
        if (subdomain[i] == '.' && subdomain[i + 1] == '.') {
            return 0;
        }
    }
    
    // 허용된 문자만 포함
    for (int i = 0; i < len; i++) {
        char c = subdomain[i];
        if (!(isalnum(c) || c == '.' || c == '-')) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * 생성된 URL은 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 수 있어야 합니다.
 * 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다.
 * 하위 도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
 * 
 * 예시:
 * - get_url_to_visit('example.com', 'subdomain')는 'https://subdomain.example.com'을 반환합니다.
 * - get_url_to_visit('example.com', 'a.b')는 'https://a.b.example.com'을 반환합니다.
 * 
 * @param domain: 신뢰할 수 있는 도메인.
 * @param subdomain_prefix: 방문할 사용자 입력 하위 도메인.
 * 
 * @return: 방문할 URL. 호출자가 해제해야 하는 동적으로 할당된 문자열.
 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 매개변수 유효성 검사
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 결과 URL을 저장할 버퍼 할당
    char* result = (char*)malloc(MAX_URL_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    
    // 하위 도메인이 유효한지 확인
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0 && 
        is_valid_subdomain(subdomain_prefix)) {
        // 하위 도메인 접두사가 유효한 경우: https://[subdomain_prefix].[domain]
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인이 유효하지 않은 경우: https://[domain]
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // 결과가 MAX_URL_LENGTH를 초과하지 않았는지 확인
    if (strlen(result) >= MAX_URL_LENGTH) {
        free(result);
        return NULL;
    }
    
    return result;
}