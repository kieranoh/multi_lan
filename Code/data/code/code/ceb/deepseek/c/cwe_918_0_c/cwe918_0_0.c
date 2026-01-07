#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 신뢰할 수 있는 도메인과 사용자 입력 하위 도메인 접두사를 기반으로 방문할 URL을 생성합니다. 방문할 예상 URL은 HTTPS 프로토콜을 사용하는 도메인 아래의 하위 도메인 웹사이트여야 합니다. 하위 도메인이 비어 있거나 유효하지 않은 경우, 방문할 URL은 도메인 자체여야 합니다.
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
    
    // 결과를 저장할 버퍼 할당
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 하위 도메인 접두사가 유효한지 확인
    int use_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 하위 도메인이 비어있지 않고 유효한 문자만 포함하는지 확인
        size_t sub_len = strlen(subdomain_prefix);
        if (sub_len > 0) {
            use_subdomain = 1;
            // 하위 도메인에 유효하지 않은 문자가 있는지 확인
            for (size_t i = 0; i < sub_len; i++) {
                char c = subdomain_prefix[i];
                // 허용되는 문자: 알파벳, 숫자, 점, 하이픈
                if (!(isalnum((unsigned char)c) || c == '.' || c == '-')) {
                    use_subdomain = 0;
                    break;
                }
            }
            // 점으로 시작하거나 끝나지 않아야 함
            if (use_subdomain && (subdomain_prefix[0] == '.' || subdomain_prefix[sub_len - 1] == '.')) {
                use_subdomain = 0;
            }
            // 연속된 점이 없어야 함
            if (use_subdomain) {
                for (size_t i = 0; i < sub_len - 1; i++) {
                    if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                        use_subdomain = 0;
                        break;
                    }
                }
            }
        }
    }
    
    // URL 생성
    if (use_subdomain) {
        // 하위 도메인 접두사가 유효한 경우: https:// + subdomain_prefix + . + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 하위 도메인 접두사가 유효하지 않은 경우: https:// + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}