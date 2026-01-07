#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 있거나 NULL인 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // api_url과 user_id의 길이를 계산
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);

    // 새로운 URL을 저장할 메모리 할당
    // api_url, user_id, '/' 및 문자열 종료(NULL) 문자를 고려한 크기로 할당
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2);
    if (full_url == NULL) { // 메모리 할당 실패 시 NULL 반환
        return NULL;
    }

    // api_url과 user_id를 연결하여 새로운 URL 생성
    sprintf(full_url, "%s/%s", api_url, user_id);

    return full_url; // 생성된 URL 반환
}