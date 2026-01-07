#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    /* 사용자 ID가 NULL이거나 빈 문자열인지 확인 */
    if (user_id == NULL || user_id[0] == '\0') {
        return NULL;
    }

    /* 사용자 ID가 유효한지 확인 (최소 하나의 문자 포함) */
    int valid = 0;
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (isalnum((unsigned char)user_id[i])) {
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        return NULL;
    }

    /* API URL이 NULL이거나 빈 문자열인지 확인 */
    if (api_url == NULL || api_url[0] == '\0') {
        return NULL;
    }

    /* 필요한 메모리 계산: api_url + '/' + user_id + null 종결자 */
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;

    /* 메모리 할당 */
    char* result = (char*)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    /* URL 구성 */
    strcpy(result, api_url);
    result[api_url_len] = '/';
    strcpy(result + api_url_len + 1, user_id);

    return result;
}