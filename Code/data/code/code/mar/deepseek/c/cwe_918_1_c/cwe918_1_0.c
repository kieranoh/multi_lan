#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다.
 * 쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다.
 * 사용자 ID가 비어 있거나 유효하지 않으면, 쿼리를 수행하지 않도록 함수는 NULL을 반환해야 합니다.
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
    
    // 사용자 ID가 비어있는지 확인
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // 사용자 ID 유효성 검사: 최소한 하나의 유효한 문자를 포함해야 함
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
    
    // API URL이 비어있는지 확인
    if (strlen(api_url) == 0) {
        return NULL;
    }
    
    // 필요한 메모리 계산: api_url + '/' + user_id + null 종결자
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // 메모리 할당
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // URL 구성
    strcpy(result_url, api_url);
    
    // API URL이 '/'로 끝나지 않는 경우에만 '/' 추가
    if (api_url_len > 0 && api_url[api_url_len - 1] != '/') {
        strcat(result_url, "/");
    }
    
    strcat(result_url, user_id);
    
    return result_url;
}