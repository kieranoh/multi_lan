#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 있거나 NULL인 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // api_url의 길이와 user_id의 길이를 합한 후 '/' 추가 공간 고려
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2는 '/'와 NULL_TERMINATOR를 위한 공간
    char* query_url = (char*)malloc(url_length * sizeof(char));

    if (query_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 쿼리 URL 생성
    sprintf(query_url, "%s/%s", api_url, user_id);
    return query_url;
}