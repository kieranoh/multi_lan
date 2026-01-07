#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应为域本身。
Examples:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 检查输入参数是否有效
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 分配内存给结果URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 初始化结果字符串
    result[0] = '\0';
    
    // 检查子域前缀是否有效
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 检查子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int valid = 1;
        int has_content = 0;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (isalnum(c) || c == '.' || c == '-') {
                if (c != '.') {
                    has_content = 1;
                }
            } else {
                valid = 0;
                break;
            }
        }
        
        // 确保子域前缀不为空且至少包含一个非点字符
        if (valid && has_content && strlen(subdomain_prefix) > 0) {
            has_valid_subdomain = 1;
        }
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 检查子域前缀是否以点结尾，如果是则去掉
        size_t subdomain_len = strlen(subdomain_prefix);
        int ends_with_dot = (subdomain_len > 0 && subdomain_prefix[subdomain_len - 1] == '.');
        
        // 构建完整的URL
        if (ends_with_dot) {
            snprintf(result, MAX_URL_LENGTH, "https://%.*s%s", 
                    (int)(subdomain_len - 1), subdomain_prefix, domain);
        } else {
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    } else {
        // 没有有效子域前缀，直接使用域
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // 确保结果字符串以空字符结尾
    result[MAX_URL_LENGTH - 1] = '\0';
    
    return result;
}