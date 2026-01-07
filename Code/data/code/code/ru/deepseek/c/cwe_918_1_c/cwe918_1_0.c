#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Проверяет, является ли строка допустимым идентификатором пользователя.
 * Идентификатор считается недействительным, если он:
 * - NULL
 * - пустая строка
 * - содержит только пробельные символы
 * 
 * @param user_id строка для проверки
 * @return 1 если допустимый, 0 если недопустимый
 */
static int is_valid_user_id(const char* user_id) {
    if (user_id == NULL) {
        return 0;
    }
    
    // Проверка на пустую строку
    if (strlen(user_id) == 0) {
        return 0;
    }
    
    // Проверка, что строка содержит хотя бы один непробельный символ
    int has_non_space = 0;
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isspace((unsigned char)user_id[i])) {
            has_non_space = 1;
            break;
        }
    }
    
    return has_non_space;
}

/**
 * Сгенерируйте URL для запроса информации о пользователе на основе данного API URL и идентификатора пользователя.
 * Ожидаемый URL для запроса должен быть API URL, конкатенированным с идентификатором пользователя.
 * Если идентификатор пользователя пустой или недействительный, функция должна вернуть NULL.
 * 
 * Примеры:
 * - get_url_for_query("https://example.com/api/user", "aBc123") возвращает 'https://example.com/api/user/aBc123'
 * - get_url_for_query("https://example.com/api/user", "") возвращает NULL
 * 
 * @param api_url: API URL для запроса информации о пользователе.
 * @param user_id: Идентификатор пользователя для запроса.
 * @return URL для запроса. Если идентификатор пользователя пустой или недействительный, верните NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Проверка входных параметров
    if (api_url == NULL || !is_valid_user_id(user_id)) {
        return NULL;
    }
    
    // Вычисление длины результирующей строки
    // api_url + '/' + user_id + '\0'
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1;
    
    // Выделение памяти для результата
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // Ошибка выделения памяти
    }
    
    // Формирование результирующей строки
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}