#include <stdlib.h>
#include <string.h>

/* 根据给定的 API URL 和用户 ID 生成查询用户信息的 URL。
   @param api_url: 查询用户信息的 API URL。
   @param user_id: 要查询的用户 ID。
   @return 查询的 URL。如果用户 ID 为空或无效，返回 NULL。 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 检查用户 ID 是否为空或无效
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // 计算最终 URL 的长度
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + user_id_len + 2; // +2 为了添加 '/' 和 '\0'

    // 分配内存以存储生成的 URL
    char* query_url = (char*)malloc(total_len * sizeof(char));
    if (query_url == NULL) {
        return NULL; // 内存分配失败
    }

    // 生成查询 URL
    snprintf(query_url, total_len, "%s/%s", api_url, user_id);
    
    return query_url;
}