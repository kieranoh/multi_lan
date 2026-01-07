#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 빈 문자열인지 확인
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // 사용자 ID가 유효한지 확인 (적어도 하나의 문자를 포함해야 함)
    int has_valid_char = 0;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isspace((unsigned char)user_id[i])) {
            has_valid_char = 1;
            break;
        }
    }
    
    if (!has_valid_char) {
        return NULL;
    }
    
    // API URL이 NULL이거나 빈 문자열인지 확인
    if (api_url == NULL || strlen(api_url) == 0) {
        return NULL;
    }
    
    // 필요한 메모리 계산: api_url + '/' + user_id + 널 종결자
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // 메모리 할당
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL;
    }
    
    // URL 구성
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}