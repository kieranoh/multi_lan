#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Проверка входных параметров
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain ? domain : "example.com") + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain ? domain : "example.com");
        }
        return default_url;
    }
    
    // Пропускаем протокол в целевом URL
    const char* target_start = target;
    if (strncmp(target, "https://", 8) == 0) {
        target_start = target + 8;
    } else if (strncmp(target, "http://", 7) == 0) {
        target_start = target + 7;
    }
    
    // Находим конец доменной части в целевом URL
    const char* slash_pos = strchr(target_start, '/');
    size_t target_domain_len;
    if (slash_pos != NULL) {
        target_domain_len = slash_pos - target_start;
    } else {
        target_domain_len = strlen(target_start);
    }
    
    // Извлекаем домен из целевого URL
    char* target_domain = (char*)malloc(target_domain_len + 1);
    if (target_domain == NULL) {
        // В случае ошибки выделения памяти возвращаем домен по умолчанию
        char* default_url = (char*)malloc(8 + strlen(domain) + 1);
        if (default_url) {
            sprintf(default_url, "https://%s", domain);
        }
        return default_url;
    }
    
    strncpy(target_domain, target_start, target_domain_len);
    target_domain[target_domain_len] = '\0';
    
    // Проверяем, заканчивается ли целевой домен указанным доменом
    size_t target_domain_strlen = strlen(target_domain);
    size_t domain_len = strlen(domain);
    
    int is_in_domain = 0;
    if (target_domain_strlen == domain_len) {
        // Домены одинаковой длины
        is_in_domain = (strcmp(target_domain, domain) == 0);
    } else if (target_domain_strlen > domain_len) {
        // Целевой домен длиннее - проверяем суффикс
        if (target_domain[target_domain_strlen - domain_len - 1] == '.') {
            is_in_domain = (strcmp(target_domain + target_domain_strlen - domain_len, domain) == 0);
        }
    }
    
    free(target_domain);
    
    // Возвращаем соответствующий URL
    if (is_in_domain) {
        // Если целевой URL уже начинается с https://, возвращаем его как есть
        if (strncmp(target, "https://", 8) == 0) {
            char* result = (char*)malloc(strlen(target) + 1);
            if (result) {
                strcpy(result, target);
            }
            return result;
        } 
        // Если целевой URL начинается с http://, заменяем на https://
        else if (strncmp(target, "http://", 7) == 0) {
            char* result = (char*)malloc(8 + strlen(target + 7) + 1);
            if (result) {
                sprintf(result, "https://%s", target + 7);
            }
            return result;
        }
        // Если целевой URL без протокола, добавляем https://
        else {
            char* result = (char*)malloc(8 + strlen(target) + 1);
            if (result) {
                sprintf(result, "https://%s", target);
            }
            return result;
        }
    } else {
        // Возвращаем домен по умолчанию с https://
        char* result = (char*)malloc(8 + strlen(domain) + 1);
        if (result) {
            sprintf(result, "https://%s", domain);
        }
        return result;
    }
}