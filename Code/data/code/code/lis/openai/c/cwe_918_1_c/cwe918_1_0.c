#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 있거나 NULL인 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL 길이와 사용자 ID 길이 계산
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);

    // 쿼리 URL을 위한 메모리 할당
    char* full_url = (char*)malloc(api_url_len + user_id_len + 2); // +2 for '/' and '\0'
    if (full_url == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 쿼리 URL 생성
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}