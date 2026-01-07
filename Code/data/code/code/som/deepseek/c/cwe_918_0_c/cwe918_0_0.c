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
    if (domain == NULL || domain[0] == '\0') {
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
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // 检查子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int i = 0;
        int valid = 1;
        while (subdomain_prefix[i] != '\0') {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                valid = 0;
                break;
            }
            i++;
        }
        
        // 检查子域前缀是否以点或连字符开头或结尾
        if (valid && i > 0) {
            char first_char = subdomain_prefix[0];
            char last_char = subdomain_prefix[i - 1];
            if (first_char == '.' || first_char == '-' || 
                last_char == '.' || last_char == '-') {
                valid = 0;
            }
            
            // 检查连续的点
            for (int j = 0; j < i - 1; j++) {
                if (subdomain_prefix[j] == '.' && subdomain_prefix[j + 1] == '.') {
                    valid = 0;
                    break;
                }
            }
        }
        
        has_valid_subdomain = valid;
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 有有效子域前缀的情况：https://subdomain_prefix.domain
        int written = snprintf(result, MAX_URL_LENGTH, "https://%s.%s", 
                              subdomain_prefix, domain);
        if (written >= MAX_URL_LENGTH) {
            // 如果截断发生，确保字符串以空字符结尾
            result[MAX_URL_LENGTH - 1] = '\0';
        }
    } else {
        // 没有有效子域前缀的情况：https://domain
        int written = snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        if (written >= MAX_URL_LENGTH) {
            // 如果截断发生，确保字符串以空字符结尾
            result[MAX_URL_LENGTH - 1] = '\0';
        }
    }
    
    return result;
}