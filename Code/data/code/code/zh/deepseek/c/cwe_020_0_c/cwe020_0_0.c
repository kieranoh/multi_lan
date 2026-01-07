#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
    // 检查输入参数是否有效
    if (target == NULL || domain == NULL) {
        char* fallback = (char*)malloc(9 + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // 检查目标是否以 "https://" 开头
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // 目标不以 https:// 开头，回退到域
        char* fallback = (char*)malloc(9 + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // 提取目标的主机部分
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }
    
    // 检查主机是否以域结尾
    size_t domain_len = strlen(domain);
    
    if (host_len >= domain_len) {
        const char* host_domain_part = host_start + (host_len - domain_len);
        
        // 检查域是否匹配
        if (strcmp(host_domain_part, domain) == 0) {
            // 检查域前是否有 '.' 或者是完全匹配
            if (host_len == domain_len || 
                (host_len > domain_len && *(host_domain_part - 1) == '.')) {
                // 目标在域内，返回目标的副本
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) return NULL;
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // 目标不在域内，回退到域
    char* fallback = (char*)malloc(9 + strlen(domain) + 1);
    if (fallback == NULL) return NULL;
    sprintf(fallback, "https://%s", domain);
    return fallback;
}