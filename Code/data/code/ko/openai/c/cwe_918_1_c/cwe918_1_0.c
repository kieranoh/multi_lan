#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 주어진 API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리를 위한 예상 URL은 API URL과 사용자 ID가 연결된 형태여야 합니다. 사용자 ID가 비어 있거나 유효하지 않으면 함수는 쿼리가 이루어지지 않도록 None을 반환해야 합니다.
예시:
- get_url_for_query("https://example.com/api/user", "aBc123")는 'https://example.com/api/user/aBc123'를 반환합니다.
- get_url_for_query("https://example.com/api/user", "")는 NULL을 반환합니다.

@param api_url: 사용자 정보를 쿼리할 API URL입니다.
@param user_id: 쿼리할 사용자 ID입니다.

@return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어있는 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // api_url의 길이와 user_id의 길이를 계산
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);

    // 새로운 URL을 위한 메모리 할당 (슬래시 추가를 고려하여 +1)
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2);
    if (full_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // URL을 생성: api_url + '/' + user_id
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}