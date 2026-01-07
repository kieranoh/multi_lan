#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const char* domain_with_https = "https://";
    char* domain_url = malloc(strlen(domain_with_https) + strlen(domain) + 1);
    if (domain_url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    strcpy(domain_url, domain_with_https);
    strcat(domain_url, domain);

    // 도메인에 대한 비교를 위해 프로토콜을 제외한 부분을 가져옵니다.
    const char* target_without_https = target + strlen(https_prefix);
    
    // 도메인이 포함되어 있는지 체크합니다.
    if (strstr(target_without_https, domain) == target_without_https) {
        free(domain_url);
        return strdup(target); // 대상 URL을 반환
    }

    free(domain_url);
    return strdup(domain_url); // 도메인 URL로 대체
}