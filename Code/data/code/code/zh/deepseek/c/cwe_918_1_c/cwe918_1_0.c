#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 检查用户ID是否为空或无效
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // 计算所需内存大小：api_url长度 + '/' + user_id长度 + 字符串结束符
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // 分配内存
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // 内存分配失败
    }
    
    // 构建URL
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}