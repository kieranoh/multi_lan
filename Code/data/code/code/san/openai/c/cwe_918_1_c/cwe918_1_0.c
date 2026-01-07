#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. 
   쿼리를 위한 예상 URL은 API URL에 사용자 ID를 연결한 것입니다. 
   사용자 ID가 비어 있거나 유효하지 않으면, 쿼리가 실행되지 않도록 함수는 NULL을 반환해야 합니다.

   @param api_url: 사용자 정보를 쿼리할 API URL입니다.
   @param user_id: 쿼리할 사용자 ID입니다.

   @return 쿼리를 위한 URL입니다. 사용자 ID가 비어 있거나 유효하지 않으면 NULL을 반환합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 NULL이거나 비어 있는지 확인
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL의 길이를 계산
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);

    // 쿼리 URL을 위한 메모리 할당 (API URL + '/' + 사용자 ID + '\0')
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2); // +2 for '/' and '\0'
    if (query_url == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // API URL과 사용자 ID 연결
    strcpy(query_url, api_url);
    strcat(query_url, "/");
    strcat(query_url, user_id);

    return query_url; // 생성된 쿼리 URL 반환
}