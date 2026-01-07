#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 있거나 NULL인 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // api_url의 길이 계산
    size_t api_url_length = strlen(api_url);
    // user_id의 길이 계산
    size_t user_id_length = strlen(user_id);
    
    // 쿼리 URL을 저장할 메모리 할당 (슬래시 추가를 위해 +1)
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2);
    
    // 메모리 할당 실패 시 NULL 반환
    if (query_url == NULL) {
        return NULL;
    }

    // URL 생성: api_url + "/" + user_id
    sprintf(query_url, "%s/%s", api_url, user_id);
    
    return query_url;
}