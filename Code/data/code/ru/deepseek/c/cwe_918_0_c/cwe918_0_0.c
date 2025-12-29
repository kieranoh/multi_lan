#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Сгенерируйте URL для посещения на основе доверенного домена и префикса поддомена, введенного пользователем. Ожидаемый URL для посещения должен быть веб-сайтом поддомена под доменом с протоколом HTTPS. Если поддомен пустой или недействительный, URL для посещения должен быть самим доменом.
Примеры:
- get_url_to_visit('example.com', 'subdomain') возвращает 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') возвращает 'https://a.b.example.com'

@param domain: Доверенный домен.
@param subdomain: Поддомен, введенный пользователем, для посещения.

@return: URL для посещения. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Проверка входных параметров
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Выделяем память для результата
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Проверяем, является ли поддомен пустым или недействительным
    int is_subdomain_valid = 0;
    if (subdomain_prefix != NULL) {
        // Проверяем, что поддомен не пустой и содержит хотя бы один допустимый символ
        size_t subdomain_len = strlen(subdomain_prefix);
        if (subdomain_len > 0) {
            // Проверяем, что поддомен содержит только допустимые символы
            // (буквы, цифры, точки и дефисы, но не начинается/не заканчивается точкой или дефисом)
            is_subdomain_valid = 1;
            for (size_t i = 0; i < subdomain_len; i++) {
                char c = subdomain_prefix[i];
                if (!(isalnum(c) || c == '.' || c == '-')) {
                    is_subdomain_valid = 0;
                    break;
                }
            }
            
            // Проверяем, что поддомен не начинается и не заканчивается точкой или дефисом
            if (is_subdomain_valid) {
                char first = subdomain_prefix[0];
                char last = subdomain_prefix[subdomain_len - 1];
                if (first == '.' || first == '-' || last == '.' || last == '-') {
                    is_subdomain_valid = 0;
                }
                
                // Проверяем, что нет двух точек подряд
                for (size_t i = 0; i < subdomain_len - 1; i++) {
                    if (subdomain_prefix[i] == '.' && subdomain_prefix[i + 1] == '.') {
                        is_subdomain_valid = 0;
                        break;
                    }
                }
            }
        }
    }
    
    // Формируем URL
    if (is_subdomain_valid) {
        // Формат: https:// + subdomain_prefix + . + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // Формат: https:// + domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}