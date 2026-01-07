#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어있는 경우 NULL을 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이와 사용자 ID의 길이를 계산
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);

    // 쿼리 URL을 위한 메모리를 할당 (API URL + '/' + 사용자 ID + NULL 종료 문자)
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2);
    if (query_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 쿼리 URL을 생성
    sprintf(query_url, "%s/%s", api_url, user_id);

    return query_url; // 생성된 URL 반환
}