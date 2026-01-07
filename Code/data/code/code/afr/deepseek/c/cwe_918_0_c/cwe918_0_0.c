#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应为域本身。
Examples:
- get_url_to_visit('example.com', 'subdomain') returns 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returns 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 检查输入参数是否有效
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // 分配内存用于存储结果URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 检查子域前缀是否有效
    int has_valid_subdomain = 0;
    if (subdomain_prefix != NULL) {
        // 检查子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int valid_chars = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid_chars = 0;
                break;
            }
        }
        
        // 检查子域前缀是否为空或仅包含空白字符
        int is_empty = 1;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            if (!isspace(subdomain_prefix[i])) {
                is_empty = 0;
                break;
            }
        }
        
        has_valid_subdomain = (strlen(subdomain_prefix) > 0 && !is_empty && valid_chars);
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 移除子域前缀末尾的点（如果有）
        char cleaned_subdomain[MAX_URL_LENGTH];
        strcpy(cleaned_subdomain, subdomain_prefix);
        
        // 移除前导和尾随空白字符
        size_t start = 0;
        while (isspace(cleaned_subdomain[start])) {
            start++;
        }
        
        size_t end = strlen(cleaned_subdomain) - 1;
        while (end > start && isspace(cleaned_subdomain[end])) {
            end--;
        }
        
        // 复制清理后的子域
        char trimmed_subdomain[MAX_URL_LENGTH];
        size_t j = 0;
        for (size_t i = start; i <= end; i++) {
            trimmed_subdomain[j++] = cleaned_subdomain[i];
        }
        trimmed_subdomain[j] = '\0';
        
        // 移除末尾的点（如果有）
        if (j > 0 && trimmed_subdomain[j-1] == '.') {
            trimmed_subdomain[j-1] = '\0';
            j--;
        }
        
        // 构建完整URL
        if (strlen(trimmed_subdomain) > 0) {
            snprintf(result, MAX_URL_LENGTH, "https://%s.%s", trimmed_subdomain, domain);
        } else {
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // 没有有效子域前缀，直接使用域
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}