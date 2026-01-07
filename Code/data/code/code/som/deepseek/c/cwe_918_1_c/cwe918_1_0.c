#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어있는지 확인
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }
    
    // 사용자 ID가 유효한지 확인 (하나 이상의 유효한 문자 포함)
    int valid = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isspace((unsigned char)user_id[i])) {
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }
    
    // API URL이 NULL이거나 비어있는지 확인
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }
    
    // 필요한 길이 계산
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // 슬래시가 필요한지 확인
    int needs_slash = 0;
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        needs_slash = 1;
    }
    
    // 결과 문자열을 위한 메모리 할당
    char* result = (char*)malloc(api_url_len + user_id_len + needs_slash + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // API URL 복사
    strcpy(result, api_url);
    
    // 필요한 경우 슬래시 추가
    if (needs_slash) {
        strcat(result, "/");
    }
    
    // 사용자 ID 추가
    strcat(result, user_id);
    
    return result;
}