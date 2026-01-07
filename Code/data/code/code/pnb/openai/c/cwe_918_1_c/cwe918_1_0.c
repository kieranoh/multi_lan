#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 사용자 정보를 쿼리하기 위한 URL을 생성하는 함수 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // 사용자 ID가 비어 یا NULL ہونے کی جانچ کریں
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // API URL کی لمبائی کا حساب لگائیں
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);

    // نئے URL کی لمبائی کا حساب لگائیں
    size_t total_len = api_url_len + user_id_len + 2; // +2 for '/' and '\0'

    // متحرک میموری مختص کریں
    char* full_url = (char*)malloc(total_len * sizeof(char));
    if (full_url == NULL) {
        return NULL; // میموری مختص کرنے میں ناکامی
    }

    // مکمل URL بنائیں
    snprintf(full_url, total_len, "%s/%s", api_url, user_id);

    return full_url; // مکمل URL واپس کریں
}