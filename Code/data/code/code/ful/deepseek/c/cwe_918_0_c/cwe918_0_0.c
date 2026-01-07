#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 检查字符串是否只包含有效的子域字符（字母、数字、连字符、点号） */
static int is_valid_subdomain_char(char c) {
    return isalnum((unsigned char)c) || c == '-' || c == '.';
}

/* 验证子域前缀是否有效 */
static int is_valid_subdomain_prefix(const char* subdomain) {
    if (subdomain == NULL || subdomain[0] == '\0') {
        return 0; /* 空字符串视为无效（需要特殊处理） */
    }
    
    /* 检查每个字符是否有效 */
    for (int i = 0; subdomain[i] != '\0'; i++) {
        if (!is_valid_subdomain_char(subdomain[i])) {
            return 0;
        }
    }
    
    /* 确保不以连字符或点号开头或结尾，且不包含连续点号 */
    if (subdomain[0] == '-' || subdomain[0] == '.' || 
        subdomain[strlen(subdomain) - 1] == '-' || 
        subdomain[strlen(subdomain) - 1] == '.') {
        return 0;
    }
    
    /* 检查连续点号 */
    for (int i = 0; subdomain[i] != '\0' && subdomain[i + 1] != '\0'; i++) {
        if (subdomain[i] == '.' && subdomain[i + 1] == '.') {
            return 0;
        }
    }
    
    return 1;
}

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应该是域本身。
示例:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain_prefix: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    char* result = (char*)malloc(MAX_URL_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    
    /* 如果子域前缀为空、无效或只包含空白字符，则直接返回域本身的URL */
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0' || 
        !is_valid_subdomain_prefix(subdomain_prefix)) {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    /* 构建完整的URL: https:// + 子域前缀 + . + 域 */
    int needed_length = snprintf(NULL, 0, "https://%s.%s", subdomain_prefix, domain);
    if (needed_length >= MAX_URL_LENGTH) {
        /* 如果超过最大长度，则截断子域部分 */
        int domain_len = strlen(domain);
        int prefix_available_len = MAX_URL_LENGTH - 11 - domain_len; /* 11 = "https://" + "." + null terminator */
        
        if (prefix_available_len <= 0) {
            /* 如果域本身太长，则只返回域 */
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
            return result;
        }
        
        /* 复制子域前缀的可用部分 */
        char truncated_prefix[prefix_available_len + 1];
        strncpy(truncated_prefix, subdomain_prefix, prefix_available_len);
        truncated_prefix[prefix_available_len] = '\0';
        
        /* 确保不以点号或连字符结尾 */
        while (prefix_available_len > 0 && 
               (truncated_prefix[prefix_available_len - 1] == '.' || 
                truncated_prefix[prefix_available_len - 1] == '-')) {
            truncated_prefix[--prefix_available_len] = '\0';
        }
        
        if (truncated_prefix[0] == '\0') {
            /* 如果截断后子域为空，则只返回域 */
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
            return result;
        }
        
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", truncated_prefix, domain);
        return result;
    }
    
    /* 正常情况：长度在限制内 */
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return result;
}