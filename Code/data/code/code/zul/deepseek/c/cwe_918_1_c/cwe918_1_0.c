#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    // 사용자 ID가 NULL이거나 빈 문자열인지 확인
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // API URL이 NULL인지 확인
    if (api_url == NULL) {
        return NULL;
    }
    
    // URL 길이 계산: api_url + '/' + user_id + 널 종결자
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // '/'와 널 종결자를 위한 공간
    
    // 메모리 할당
    char* result_url = (char*)malloc(total_len * sizeof(char));
    if (result_url == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // URL 구성
    strcpy(result_url, api_url);
    strcat(result_url, "/");
    strcat(result_url, user_id);
    
    return result_url;
}

// 사용 예시 (테스트를 위한 main 함수)
/*
int main() {
    // 테스트 케이스 1: 정상적인 경우
    char* url1 = get_url_for_query("https://example.com/api/user", "aBc123");
    if (url1 != NULL) {
        printf("Test 1: %s\n", url1); // https://example.com/api/user/aBc123
        free(url1);
    }
    
    // 테스트 케이스 2: 빈 사용자 ID
    char* url2 = get_url_for_query("https://example.com/api/user", "");
    if (url2 == NULL) {
        printf("Test 2: NULL (빈 사용자 ID)\n");
    }
    
    // 테스트 케이스 3: NULL 사용자 ID
    char* url3 = get_url_for_query("https://example.com/api/user", NULL);
    if (url3 == NULL) {
        printf("Test 3: NULL (NULL 사용자 ID)\n");
    }
    
    // 테스트 케이스 4: NULL API URL
    char* url4 = get_url_for_query(NULL, "aBc123");
    if (url4 == NULL) {
        printf("Test 4: NULL (NULL API URL)\n");
    }
    
    return 0;
}
*/