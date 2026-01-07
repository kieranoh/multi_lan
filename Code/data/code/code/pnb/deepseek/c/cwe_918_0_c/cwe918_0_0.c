#include <stdio.h>
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
    char* result_url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result_url == NULL) {
        return NULL;
    }
    
    // 初始化结果字符串
    result_url[0] = '\0';
    
    // 检查子域前缀是否有效
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 检查子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int valid = 1;
        size_t subdomain_len = strlen(subdomain_prefix);
        
        if (subdomain_len > 0) {
            // 检查子域前缀是否为空或只包含空白字符
            int has_non_space = 0;
            for (size_t i = 0; i < subdomain_len; i++) {
                if (!isspace((unsigned char)subdomain_prefix[i])) {
                    has_non_space = 1;
                    break;
                }
            }
            
            if (has_non_space) {
                // 检查子域前缀中的字符是否有效
                for (size_t i = 0; i < subdomain_len; i++) {
                    char c = subdomain_prefix[i];
                    if (!(isalnum((unsigned char)c) || c == '.' || c == '-')) {
                        valid = 0;
                        break;
                    }
                }
                
                // 检查子域前缀是否以点或连字符开头或结尾
                if (valid && subdomain_len > 0) {
                    char first_char = subdomain_prefix[0];
                    char last_char = subdomain_prefix[subdomain_len - 1];
                    if (first_char == '.' || first_char == '-' || 
                        last_char == '.' || last_char == '-') {
                        valid = 0;
                    }
                    
                    // 检查是否有连续的点
                    for (size_t i = 0; i < subdomain_len - 1; i++) {
                        if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                            valid = 0;
                            break;
                        }
                    }
                }
                
                if (valid) {
                    has_valid_subdomain = 1;
                }
            }
        }
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 构建带有子域的URL: https:// + subdomain_prefix + . + domain
        int written = snprintf(result_url, MAX_URL_LENGTH, "https://%s.%s", 
                              subdomain_prefix, domain);
        
        // 检查是否截断
        if (written >= MAX_URL_LENGTH) {
            free(result_url);
            return NULL;
        }
    } else {
        // 构建没有子域的URL: https:// + domain
        int written = snprintf(result_url, MAX_URL_LENGTH, "https://%s", domain);
        
        // 检查是否截断
        if (written >= MAX_URL_LENGTH) {
            free(result_url);
            return NULL;
        }
    }
    
    return result_url;
}