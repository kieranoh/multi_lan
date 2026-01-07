#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Проверка на допустимость домена и префикса поддомена
    if (domain == NULL || strlen(domain) == 0) {
        return NULL; // Если домен недействителен, возвращаем NULL
    }

    // Проверка на пустой префикс поддомена
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Если префикс поддомена пустой, возвращаем URL домена
        char* url = (char*)malloc(MAX_URL_LENGTH);
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }

    // Проверка длины префикса поддомена
    if (strlen(subdomain_prefix) + strlen(domain) + 8 > MAX_URL_LENGTH) {
        return NULL; // Если итоговая длина превышает лимит, возвращаем NULL
    }

    // Создание полного URL с поддоменом
    char* url = (char*)malloc(MAX_URL_LENGTH);
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    return url;
}