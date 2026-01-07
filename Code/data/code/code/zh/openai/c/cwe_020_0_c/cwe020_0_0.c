#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 检查提供的目标 URL 字符串是否在提供的域内。
如果是，返回用于重定向的目标 URL；否则，回退到用于重定向的域 URL。
使用 https 协议。

示例：
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: 目标 URL 字符串。
@param domain: 域字符串，不带协议。

@return 用于重定向的 URL 字符串。 */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* http_prefix = "https://";
    size_t domain_len = strlen(domain);
    
    // Check if the target URL starts with the https prefix
    if (strncmp(target, http_prefix, strlen(http_prefix)) == 0) {
        const char* host_start = target + strlen(http_prefix);
        const char* host_end = strchr(host_start, '/');
        size_t host_len = (host_end != NULL) ? (host_end - host_start) : strlen(host_start);
        
        // Check if the host is the same as the domain or a subdomain of it
        if (host_len >= domain_len && strcasecmp(host_start + host_len - domain_len, domain) == 0) {
            // Valid domain or subdomain, return the original target URL
            return strdup(target);
        }
    }
    
    // If not valid, return the domain URL
    char* redirect_url = malloc(strlen(http_prefix) + strlen(domain) + 1);
    if (redirect_url == NULL) {
        return NULL; // Memory allocation failed
    }
    sprintf(redirect_url, "%s%s", http_prefix, domain);
    return redirect_url;
}