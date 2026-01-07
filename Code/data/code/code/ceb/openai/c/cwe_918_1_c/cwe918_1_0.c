#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다. 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 None을 반환해야 합니다.
예시:
- get_url_for_query("https://example.com/api/user", "aBc123")는 'https://example.com/api/user/aBc123'을 반환합니다.
- get_url_for_query("https://example.com/api/user", "")는 NULL을 반환합니다.

@param api_url: 사용자 정보를 쿼리할 API URL입니다.
@param user_id: 쿼리할 사용자 ID입니다.

@return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if api_url or user_id is NULL or if user_id is empty
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Calculate the length for the new URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    
    // Allocate memory for the new URL string
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2); // +2 for '/' and '\0'
    if (query_url == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Create the new URL
    sprintf(query_url, "%s/%s", api_url, user_id);
    
    return query_url;
}