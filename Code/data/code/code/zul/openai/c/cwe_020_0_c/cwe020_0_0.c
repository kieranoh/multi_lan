#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 제공된 대상 URL 문자열이 제공된 도메인 내에 있는지 확인합니다.
그렇다면 리디렉션을 위해 대상 URL을 반환하고, 그렇지 않으면 리디렉션을 위해 도메인 URL로 대체합니다.
https 프로토콜을 사용합니다.

Examples:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 대상 URL 문자열입니다.
@param domain: 프로토콜을 제외한 도메인 문자열입니다.

@return 리디렉션을 위한 URL 문자열입니다. */
char* get_target_for_redirect(const char* target, const char* domain) {
    // 도메인 길이 확인
    size_t domain_len = strlen(domain);
    
    // 대상 URL이 "https://"로 시작하는지 확인
    if (strncmp(target, "https://", 8) == 0) {
        // 대상 URL에서 호스트를 추출
        const char* host_start = target + 8; // "https://".length = 8
        const char* host_end = strchr(host_start, '/'); // 경로의 시작을 찾기
        if (host_end == NULL) {
            host_end = target + strlen(target); // 경로가 없는 경우 전체를 사용
        }

        // 호스트 문자열의 길이 확인
        size_t host_len = host_end - host_start;

        // 도메인과 비교
        if (host_len >= domain_len && strncmp(host_start, domain, domain_len) == 0) {
            // 도메인이 일치하면 원본 URL 반환
            return strdup(target);
        }
    }

    // 도메인이 일치하지 않으면 기본 도메인 URL 반환
    char* redirect_url = (char*)malloc(strlen("https://") + strlen(domain) + 1);
    strcpy(redirect_url, "https://");
    strcat(redirect_url, domain);
    
    return redirect_url;
}