#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다. 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 수행되지 않도록 함수는 None을 반환해야 합니다.
예시:
- get_url_for_query("https://example.com/api/user", "aBc123")는 'https://example.com/api/user/aBc123'을 반환합니다.
- get_url_for_query("https://example.com/api/user", "")는 NULL을 반환합니다.

@param api_url: 사용자 정보를 쿼리할 API URL입니다.
@param user_id: 쿼리할 사용자 ID입니다.

@return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어 있는 경우 NULL 반환
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이 계산
    size_t api_url_length = strlen(api_url);
    // 사용자 ID의 길이 계산
    size_t user_id_length = strlen(user_id);

    // 최종 URL을 저장할 메모리 할당 (슬래시와 널 종료 포함)
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2);
    if (full_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 최종 URL 생성
    snprintf(full_url, api_url_length + user_id_length + 2, "%s/%s", api_url, user_id);
    
    return full_url;
}