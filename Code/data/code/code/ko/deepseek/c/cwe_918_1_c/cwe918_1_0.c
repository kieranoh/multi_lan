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
    /* 사용자 ID가 NULL이거나 빈 문자열인지 확인 */
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }

    /* API URL이 NULL인지 확인 */
    if (api_url == NULL) {
        return NULL;
    }

    /* 필요한 메모리 크기 계산: api_url + '/' + user_id + 널 종결자 */
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; /* '/'와 널 종결자를 위한 공간 */

    /* 메모리 할당 */
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; /* 메모리 할당 실패 */
    }

    /* URL 구성 */
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);

    return result_url;
}