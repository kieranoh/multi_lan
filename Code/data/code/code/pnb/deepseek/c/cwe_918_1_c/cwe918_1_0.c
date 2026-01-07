#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 사용자 ID가 유효한지 검사합니다.
 * 유효한 사용자 ID는 비어 있지 않고, 공백 문자만으로 구성되지 않아야 합니다.
 * 
 * @param user_id 검사할 사용자 ID
 * @return 유효하면 1, 그렇지 않으면 0
 */
static int is_valid_user_id(const char* user_id) {
    if (user_id == NULL) {
        return 0;
    }
    
    // 빈 문자열인지 확인
    if (strlen(user_id) == 0) {
        return 0;
    }
    
    // 공백 문자만으로 구성되었는지 확인
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isspace((unsigned char)user_id[i])) {
            return 1;
        }
    }
    
    return 0;
}

/**
 * API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 NULL을 반환합니다.
 * 
 * @param api_url 사용자 정보를 쿼리할 API URL입니다.
 * @param user_id 쿼리할 사용자 ID입니다.
 * @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 매개변수 유효성 검사
    if (api_url == NULL || !is_valid_user_id(user_id)) {
        return NULL;
    }
    
    // API URL 길이 계산
    size_t api_url_len = strlen(api_url);
    
    // URL 구분자 '/'가 필요한지 확인
    int needs_slash = 0;
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        needs_slash = 1;
    }
    
    // 사용자 ID 길이 계산
    size_t user_id_len = strlen(user_id);
    
    // 전체 URL 길이 계산: api_url + '/' (필요한 경우) + user_id + 널 종결자
    size_t total_len = api_url_len + (needs_slash ? 1 : 0) + user_id_len + 1;
    
    // 메모리 할당
    char* result_url = (char*)malloc(total_len);
    if (result_url == NULL) {
        return NULL;
    }
    
    // URL 조립
    strcpy(result_url, api_url);
    
    if (needs_slash) {
        strcat(result_url, "/");
    }
    
    strcat(result_url, user_id);
    
    return result_url;
}