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
    // 检查输入参数的有效性
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 分配内存给结果字符串
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
        size_t len = strlen(subdomain_prefix);
        
        if (len > 0) {
            for (size_t i = 0; i < len; i++) {
                char c = subdomain_prefix[i];
                if (!(isalnum(c) || c == '.' || c == '-')) {
                    valid = 0;
                    break;
                }
            }
            
            // 确保子域不以点或连字符开头或结尾
            if (valid && len > 0) {
                if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                    subdomain_prefix[len-1] == '.' || subdomain_prefix[len-1] == '-') {
                    valid = 0;
                }
                
                // 确保没有连续的点
                for (size_t i = 0; i < len - 1; i++) {
                    if (subdomain_prefix[i] == '.' && subdomain_prefix[i+1] == '.') {
                        valid = 0;
                        break;
                    }
                }
            }
            
            has_valid_subdomain = valid && len > 0;
        }
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 构建格式: https:// + subdomain_prefix + . + domain
        int needed_length = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1; // 8 for "https://", 1 for ".", 1 for null terminator
        
        if (needed_length <= MAX_URL_LENGTH) {
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        } else {
            // 如果超过最大长度，只返回域本身
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // 没有有效子域，直接返回域的URL
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}