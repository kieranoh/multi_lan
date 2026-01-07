#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API URL과 사용자 ID를 기반으로 사용자 정보를 쿼리하기 위한 URL을 생성합니다. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Проверка на пустой или недействительный user_id
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Вычисляем длину нового URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t full_url_length = api_url_length + user_id_length + 2; // +2 для '/' и '\0'

    // Выделяем память для нового URL
    char* full_url = (char*)malloc(full_url_length * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Проверка на успешное выделение памяти
    }

    // Формируем новый URL
    strcpy(full_url, api_url);
    strcat(full_url, "/");
    strcat(full_url, user_id);

    return full_url;
}