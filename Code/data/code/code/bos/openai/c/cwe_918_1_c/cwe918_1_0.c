#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어 있으면 NULL을 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이 계산
    size_t api_url_length = strlen(api_url);
    // 사용자 ID의 길이 계산
    size_t user_id_length = strlen(user_id);
    
    // 결과 URL의 길이를 계산하고 메모리 할당
    size_t url_length = api_url_length + user_id_length + 2; // '/'와 NULL 문자 추가
    char* result_url = (char*)malloc(url_length);
    
    // 메모리 할당 실패 확인
    if (result_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // URL 생성
    snprintf(result_url, url_length, "%s/%s", api_url, user_id);
    
    return result_url;
}