#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 根据受信任的域和用户输入的子域前缀生成要访问的 URL。预期访问的 URL 应该是带有 HTTPS 协议的域下的子域网站。如果子域为空或无效，则要访问的 URL 应该是域本身。
示例:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 受信任的域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的 URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 检查输入参数是否有效
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // 分配内存用于存储结果URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 初始化结果字符串
    result[0] = '\0';
    
    // 检查子域前缀是否为空或无效
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        // 子域为空，直接使用域本身
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 验证子域前缀是否只包含有效字符（字母、数字、点、连字符）
    int valid_subdomain = 1;
    const char* p = subdomain_prefix;
    while (*p != '\0') {
        if (!isalnum((unsigned char)*p) && *p != '.' && *p != '-') {
            valid_subdomain = 0;
            break;
        }
        p++;
    }
    
    // 检查子域前缀是否以点或连字符开头或结尾，或者包含连续的点
    if (valid_subdomain) {
        size_t len = strlen(subdomain_prefix);
        if (len > 0) {
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[len-1] == '.' || subdomain_prefix[len-1] == '-') {
                valid_subdomain = 0;
            }
            
            // 检查连续的点
            for (size_t i = 0; i < len - 1; i++) {
                if (subdomain_prefix[i] == '.' && subdomain_prefix[i+1] == '.') {
                    valid_subdomain = 0;
                    break;
                }
            }
        }
    }
    
    if (!valid_subdomain) {
        // 子域无效，直接使用域本身
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 构建完整的URL
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    
    return result;
}