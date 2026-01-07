#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자가 제공한 API URL과 사용자 ID가 유효한지 확인
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // 사용자 ID를 포함한 최종 URL의 길이를 계산
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    
    // 메모리 할당
    char* query_url = (char*)malloc(url_length * sizeof(char));
    if (query_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 최종 URL 생성
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);

    return query_url; // 생성된 URL 반환
}