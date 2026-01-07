#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应该是域本身。
示例:
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
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // 初始化URL字符串
    url[0] = '\0';
    
    // 检查子域前缀是否有效
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 检查子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int valid = 1;
        int has_content = 0;
        for (size_t i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
            if (c != '.') {
                has_content = 1;
            }
        }
        
        // 检查子域前缀是否以点开头或结尾，或者包含连续的点
        if (valid && has_content) {
            size_t len = strlen(subdomain_prefix);
            if (subdomain_prefix[0] == '.' || subdomain_prefix[len - 1] == '.') {
                valid = 0;
            }
            for (size_t i = 0; i < len - 1; i++) {
                if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                    valid = 0;
                    break;
                }
            }
        }
        
        has_valid_subdomain = (valid && has_content);
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 计算预期URL长度
        size_t total_len = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1; // "https://" + subdomain + "." + domain + "\0"
        
        if (total_len <= MAX_URL_LENGTH) {
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        } else {
            // 如果URL太长，只使用域
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // 没有有效子域前缀，直接使用域
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}