#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // 도메인 길이 계산
    size_t domain_len = strlen(domain);
    
    // 프로토콜 분리 및 URL 검사
    if (strncmp(target, "https://", 8) == 0) {
        // 도메인 검사
        const char* domain_start = target + 8; // "https://" 이후
        const char* domain_end = strchr(domain_start, '/'); // 경로 시작 위치
        
        // 도메인 경로가 없으면 끝까지 계산
        if (domain_end == NULL) {
            domain_end = domain_start + strlen(domain_start);
        }
        
        size_t target_domain_len = domain_end - domain_start;
        
        // 도메인이 일치하는지 확인
        if (target_domain_len >= domain_len && strncmp(domain_start, domain, domain_len) == 0) {
            // 도메인이 일치하므로 원래 URL 반환
            return strdup(target);
        }
    }
    
    // 도메인이 일치하지 않으면 기본 도메인으로 리디렉션
    char* redirect_url = (char*)malloc(8 + domain_len + 1); // "https://" + 도메인 + '\0'
    if (redirect_url != NULL) {
        sprintf(redirect_url, "https://%s", domain);
    }
    
    return redirect_url;
}