#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어있는지 확인
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }

    // 사용자 ID가 유효한지 확인 (하나 이상의 문자를 포함해야 함)
    int has_valid_char = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isspace((unsigned char)user_id[i])) {
            has_valid_char = 1;
            break;
        }
    }
    
    if (!has_valid_char) {
        return NULL;
    }

    // API URL이 NULL이거나 비어있는지 확인
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }

    // 필요한 길이 계산
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // '/'가 필요할 수 있으므로 추가 공간 할당
    char* result = (char*)malloc(api_url_len + user_id_len + 2); // +2: '/'와 null 종결자
    
    if (result == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // URL 구성
    strcpy(result, api_url);
    
    // API URL이 '/'로 끝나지 않으면 추가
    if (api_url[api_url_len - 1] != '/') {
        strcat(result, "/");
    }
    
    strcat(result, user_id);
    
    return result;
}