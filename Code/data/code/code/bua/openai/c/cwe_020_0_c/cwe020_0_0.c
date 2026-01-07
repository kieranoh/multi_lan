#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // 도메인 앞에 "https://"를 추가합니다.
    char domain_with_protocol[256];
    snprintf(domain_with_protocol, sizeof(domain_with_protocol), "https://%s", domain);
    
    // 대상 URL이 도메인 내에 있는지 확인합니다.
    if (strstr(target, domain_with_protocol) == target) {
        // 대상 URL이 도메인 내에 있는 경우, 대상 URL을 반환합니다.
        return strdup(target);
    } else {
        // 그렇지 않은 경우, 도메인 URL로 대체합니다.
        return strdup(domain_with_protocol);
    }
}