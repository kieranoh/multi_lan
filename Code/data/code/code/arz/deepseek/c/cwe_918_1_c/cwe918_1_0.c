#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * 사용자 ID가 유효한지 검사합니다.
 * 유효한 사용자 ID는 비어 있지 않고, 공백을 포함하지 않으며,
 * 알파벳과 숫자로만 구성되어 있어야 합니다.
 * 
 * @param user_id 검사할 사용자 ID
 * @return 유효하면 1, 그렇지 않으면 0
 */
static int is_valid_user_id(const char* user_id) {
    if (user_id == NULL || strlen(user_id) == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 NULL을 반환합니다.
 * 
 * @param api_url: 사용자 정보를 쿼리할 API URL입니다.
 * @param user_id: 쿼리할 사용자 ID입니다.
 * @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 매개변수 유효성 검사
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // 사용자 ID 유효성 검사
    if (!is_valid_user_id(user_id)) {
        return NULL;
    }
    
    // API URL 길이 확인
    size_t api_url_len = strlen(api_url);
    if (api_url_len == 0) {
        return NULL;
    }
    
    // 필요한 메모리 계산: api_url + '/' + user_id + 널 종료 문자
    size_t total_len = api_url_len + 1 + strlen(user_id) + 1;
    
    // 메모리 할당
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // URL 구성
    strcpy(result_url, api_url);
    
    // API URL이 '/'로 끝나는지 확인하고 필요에 따라 추가
    if (api_url[api_url_len - 1] != '/') {
        strcat(result_url, "/");
    }
    
    // 사용자 ID 추가
    strcat(result_url, user_id);
    
    return result_url;
}