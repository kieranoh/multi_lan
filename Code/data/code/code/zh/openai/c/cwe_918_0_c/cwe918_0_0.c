#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 检查输入有效性
    if (domain == NULL || subdomain_prefix == NULL || strlen(domain) == 0 || strlen(domain) >= MAX_URL_LENGTH) {
        return NULL; // 返回 NULL 表示无效输入
    }

    // 计算子域的长度
    size_t subdomain_length = strlen(subdomain_prefix);
    if (subdomain_length == 0) {
        // 如果子域为空，直接使用域名
        char* url = (char*)malloc(MAX_URL_LENGTH);
        if (url != NULL) {
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
        return url;
    }

    // 检查子域是否有效（简单检查，确保没有非法字符）
    for (size_t i = 0; i < subdomain_length; i++) {
        if (!(subdomain_prefix[i] == '.' || (subdomain_prefix[i] >= 'a' && subdomain_prefix[i] <= 'z') || 
              (subdomain_prefix[i] >= '0' && subdomain_prefix[i] <= '9') || 
              (subdomain_prefix[i] == '-'))) {
            return NULL; // 返回 NULL 表示无效的子域
        }
    }

    // 构造最终的 URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}