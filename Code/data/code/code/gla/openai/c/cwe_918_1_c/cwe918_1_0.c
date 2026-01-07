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
    
    // 최종 URL을 저장할 메모리 할당
    // api_url의 길이 + '/' + user_id의 길이 + NULL 종료 문자
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2);
    
    // 메모리 할당 실패 시 NULL 반환
    if (full_url == NULL) {
        return NULL;
    }

    // URL 생성
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}