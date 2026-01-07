#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 있거나 NULL인 경우 NULL을 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이와 사용자 ID의 길이 계산
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);

    // 최종 URL의 길이를 계산 (API URL + '/' + 사용자 ID + NULL 종료자)
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2);
    if (full_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 최종 URL 생성
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}