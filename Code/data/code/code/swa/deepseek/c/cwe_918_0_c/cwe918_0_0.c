#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应该是域本身。
Examples:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 分配内存给返回的URL
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // 检查domain是否有效
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(url, "https://");
        return url;
    }
    
    // 检查subdomain_prefix是否有效
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // 检查subdomain_prefix是否只包含有效字符（字母、数字、点、连字符）
        int valid = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
        }
        
        // 确保不以点或连字符开头或结尾，且不包含连续的点
        if (valid && strlen(subdomain_prefix) > 0) {
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[strlen(subdomain_prefix)-1] == '.' ||
                subdomain_prefix[strlen(subdomain_prefix)-1] == '-') {
                valid = 0;
            }
            
            // 检查连续的点
            for (size_t i = 0; i < strlen(subdomain_prefix) - 1; i++) {
                if (subdomain_prefix[i] == '.' && subdomain_prefix[i+1] == '.') {
                    valid = 0;
                    break;
                }
            }
        }
        
        has_valid_subdomain = valid;
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 有有效的子域前缀：https://subdomain_prefix.domain
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 没有有效的子域前缀：https://domain
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    // 确保URL长度不超过限制
    url[MAX_URL_LENGTH - 1] = '\0';
    
    return url;
}