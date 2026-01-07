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
    const char* https_prefix = "https://";
    size_t domain_length = strlen(domain);
    
    // Ensure target starts with "https://"
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        const char* domain_pos = strstr(target, domain);
        // Check if the domain is part of the target URL
        if (domain_pos != NULL) {
            // Verify that the domain is well-formed in the URL
            if ((domain_pos == target + strlen(https_prefix)) || 
                (domain_pos[-1] == '.' && domain_pos[-2] == '.')) {
                return strdup(target); // Return the target URL
            }
        }
    }
    
    // If target is not within the domain, return the domain URL
    char* redirect_url = malloc(strlen(https_prefix) + strlen(domain) + 1);
    if (redirect_url) {
        sprintf(redirect_url, "%s%s", https_prefix, domain);
    }
    return redirect_url;
}