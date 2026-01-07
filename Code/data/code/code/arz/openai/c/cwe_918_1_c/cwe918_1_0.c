#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 확인 사용자 ID가 비어 أو NULL
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // URL의 길이를 계산합니다.
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    
    // 새 URL을 저장하기 위한 메모리 할당
    // +1 للعلامة النهائية '\0'
    char* full_url = (char*)malloc(api_url_length + user_id_length + 2); // +1 لعلامة '/' و +1 لعلامة النهاية

    // تحقق من تخصيص الذاكرة
    if (full_url == NULL) {
        return NULL;
    }
    
    // بناء URL الكامل
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}