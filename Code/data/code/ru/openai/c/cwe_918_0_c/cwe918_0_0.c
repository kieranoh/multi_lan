#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256
#define MAX_DOMAIN_LENGTH 256
#define MAX_SUBDOMAIN_LENGTH 128

bool is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return false;
    }
    // Проверка на наличие недопустимых символов
    for (const char* p = subdomain; *p; p++) {
        if (!(((*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || *p == '-' || *p == '.') && *p != '-') && 
            !(*p == '.' && p == subdomain)) { // Нельзя начинать с точки
            return false;
        }
    }
    return true;
}

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0 || strlen(domain) > MAX_DOMAIN_LENGTH) {
        return NULL; // Неверный домен
    }

    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Не удалось выделить память
    }

    if (is_valid_subdomain(subdomain_prefix)) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }

    return url;
}