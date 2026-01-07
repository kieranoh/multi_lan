#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어 있으면 NULL을 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이와 사용자 ID의 길이를 계산
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // 쿼리 URL을 위한 메모리 할당 (추가 슬래시와 널 종료 문자를 포함)
    char* query_url = (char*)malloc(api_url_len + user_id_len + 2);
    if (query_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // API URL과 사용자 ID를 연결하여 쿼리 URL 생성
    strcpy(query_url, api_url);
    strcat(query_url, "/");
    strcat(query_url, user_id);

    return query_url; // 생성된 쿼리 URL 반환
}