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
    
    // 分配内存给返回的URL
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // 初始化URL字符串
    url[0] = '\0';
    
    // 添加HTTPS协议前缀
    strcat(url, "https://");
    
    // 检查子域前缀是否有效
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // 验证子域前缀是否只包含有效字符（字母、数字、点、连字符）
        int valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                valid = 0;
                break;
            }
        }
        
        // 如果子域前缀有效，则添加到URL中
        if (valid) {
            // 检查子域前缀是否以点结尾，如果是则移除
            int len = strlen(subdomain_prefix);
            if (subdomain_prefix[len - 1] == '.') {
                // 复制子域前缀（不包括最后的点）
                char temp_subdomain[MAX_URL_LENGTH];
                strncpy(temp_subdomain, subdomain_prefix, len - 1);
                temp_subdomain[len - 1] = '\0';
                
                // 添加到URL
                strcat(url, temp_subdomain);
                strcat(url, ".");
            } else {
                // 直接添加子域前缀和点
                strcat(url, subdomain_prefix);
                strcat(url, ".");
            }
        }
    }
    
    // 添加域名
    strcat(url, domain);
    
    // 确保URL长度不超过最大限制
    if (strlen(url) >= MAX_URL_LENGTH) {
        url[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return url;
}