#include <string.h>
#include <stdlib.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어있는지 확인
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // API URL이 NULL인지 확인
    if (api_url == NULL) {
        return NULL;
    }
    
    // 필요한 메모리 계산: api_url + '/' + user_id + null 종결자
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // +1 for '/', +1 for '\0'
    
    // 메모리 할당
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // URL 구성
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}