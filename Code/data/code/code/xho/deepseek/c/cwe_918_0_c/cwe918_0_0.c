#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL;
    }
    
    // 检查domain是否有效
    if (domain == NULL || strlen(domain) == 0) {
        free(url);
        return NULL;
    }
    
    // 检查子域前缀是否为空或无效
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // 直接访问域本身
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }
    
    // 移除子域前缀开头和结尾的空格
    const char* start = subdomain_prefix;
    const char* end = subdomain_prefix + strlen(subdomain_prefix) - 1;
    
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // 如果去除空格后子域为空，直接访问域本身
    if (start > end) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }
    
    // 计算有效子域前缀的长度
    size_t prefix_len = end - start + 1;
    
    // 构建URL：https:// + 子域前缀 + . + 域
    // 检查总长度是否超过限制
    size_t total_len = 8 + prefix_len + 1 + strlen(domain) + 1; // 8为"https://"，1为"."，1为"\0"
    
    if (total_len > MAX_URL_LENGTH) {
        free(url);
        return NULL;
    }
    
    // 构建URL
    snprintf(url, MAX_URL_LENGTH, "https://%.*s.%s", (int)prefix_len, start, domain);
    
    return url;
}