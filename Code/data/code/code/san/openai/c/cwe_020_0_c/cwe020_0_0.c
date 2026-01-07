#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // 도메인 길이 계산
    size_t domain_length = strlen(domain);
    
    // 타겟 문자열이 "https://"로 시작하는지 확인
    if (strncmp(target, "https://", 8) == 0) {
        // 타겟 URL에서 "https://" 이후의 부분을 확인
        const char* after_https = target + 8;
        
        // 도메인이 타겟 URL의 시작 부분에 포함되어 있는지 확인
        if (strncmp(after_https, domain, domain_length) == 0) {
            // 도메인이 일치할 경우, 타겟 URL 반환
            return strdup(target);
        }
    }
    
    // 도메인이 일치하지 않을 경우, "https://<domain>" 반환
    char* redirect_url = (char*)malloc(8 + domain_length + 1); // "https://" + domain + null terminator
    if (redirect_url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    sprintf(redirect_url, "https://%s", domain);
    return redirect_url;
}