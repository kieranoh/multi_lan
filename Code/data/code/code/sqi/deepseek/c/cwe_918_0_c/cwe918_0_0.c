#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应该是域本身。
Examples:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 为结果URL分配内存
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 检查domain参数是否有效
    if (domain == NULL || strlen(domain) == 0) {
        strcpy(result, "https://");
        return result;
    }
    
    // 检查子域前缀是否有效
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // 子域为空或无效，直接返回域本身的HTTPS URL
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 清理子域前缀中的前导和尾随空格（如果存在）
    char cleaned_prefix[MAX_URL_LENGTH];
    strncpy(cleaned_prefix, subdomain_prefix, MAX_URL_LENGTH - 1);
    cleaned_prefix[MAX_URL_LENGTH - 1] = '\0';
    
    // 去除前导空格
    int start = 0;
    while (cleaned_prefix[start] == ' ') {
        start++;
    }
    
    // 去除尾随空格
    int end = strlen(cleaned_prefix) - 1;
    while (end >= 0 && cleaned_prefix[end] == ' ') {
        cleaned_prefix[end] = '\0';
        end--;
    }
    
    // 如果清理后子域为空，直接返回域本身的HTTPS URL
    if (strlen(cleaned_prefix + start) == 0) {
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        return result;
    }
    
    // 生成完整的URL：https:// + 子域前缀 + . + 域
    snprintf(result, MAX_URL_LENGTH, "https://%s.%s", cleaned_prefix + start, domain);
    
    return result;
}