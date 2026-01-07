#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 NULL을 반환해야 합니다.
 * 
 * @param api_url: 사용자 정보를 쿼리할 API URL입니다.
 * @param user_id: 쿼리할 사용자 ID입니다.
 * 
 * @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 입력 매개변수 검증
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // 사용자 ID가 비어 있는지 확인
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // 사용자 ID가 유효한지 확인 (알파벳과 숫자만 허용)
    int valid = 1;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }
    
    // 필요한 메모리 계산: api_url + '/' + user_id + null 종결자
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // 메모리 할당
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // URL 구성
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}