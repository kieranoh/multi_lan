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
        int i;
        for (i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
                break;
            }
        }
        has_valid_subdomain = (subdomain_prefix[i] == '\0' && i > 0);
    }
    
    // 构建URL
    if (has_valid_subdomain) {
        // 有有效子域前缀的情况：https://subdomain.domain
        int needed_length = snprintf(NULL, 0, "https://%s.%s", subdomain_prefix, domain);
        if (needed_length >= MAX_URL_LENGTH) {
            free(result);
            return NULL;
        }
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // 没有有效子域前缀的情况：https://domain
        int needed_length = snprintf(NULL, 0, "https://%s", domain);
        if (needed_length >= MAX_URL_LENGTH) {
            free(result);
            return NULL;
        }
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}