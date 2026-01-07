#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* 生成一个基于可信域和用户输入子域前缀的访问URL。预期访问的URL应该是该域下的子域网站，使用HTTPS协议。如果子域为空或无效，访问的URL应为域本身。
Examples:
- get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

@param domain: 可信域。
@param subdomain: 用户输入的要访问的子域。

@return: 要访问的URL。 */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // 分配内存给结果字符串
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // 初始化结果字符串
    result[0] = '\0';
    
    // 检查domain是否有效
    if (domain == NULL || domain[0] == '\0') {
        strcpy(result, "https://");
        return result;
    }
    
    // 检查subdomain_prefix是否有效（空或只包含空白字符）
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // 检查是否只包含空白字符
        int i = 0;
        while (subdomain_prefix[i] != '\0') {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                subdomain_valid = 1;
                break;
            }
            i++;
        }
    }
    
    // 构建URL
    strcpy(result, "https://");
    
    if (subdomain_valid) {
        // 添加子域前缀
        strcat(result, subdomain_prefix);
        
        // 确保子域以点结尾（如果还没有）
        int len = strlen(result);
        if (len > 0 && result[len-1] != '.') {
            strcat(result, ".");
        }
    }
    
    // 添加域
    strcat(result, domain);
    
    // 确保结果不超过最大长度
    if (strlen(result) >= MAX_URL_LENGTH) {
        result[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return result;
}