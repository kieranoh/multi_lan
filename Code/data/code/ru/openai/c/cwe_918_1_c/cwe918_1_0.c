#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Сгенерируйте URL для запроса информации о пользователе на основе данного API URL и идентификатора пользователя. Ожидаемый URL для запроса должен быть API URL, конкатенированным с идентификатором пользователя. Если идентификатор пользователя пустой или недействительный, функция должна вернуть NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Проверяем, что api_url и user_id не пустые
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Вычисляем длину нового URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t new_url_length = api_url_length + user_id_length + 2; // +1 для '/' и +1 для '\0'
    
    // Выделяем память для нового URL
    char* new_url = (char*)malloc(new_url_length);
    if (new_url == NULL) {
        return NULL; // Проверяем на успешное выделение памяти
    }
    
    // Формируем новый URL
    snprintf(new_url, new_url_length, "%s/%s", api_url, user_id);
    
    return new_url;
}