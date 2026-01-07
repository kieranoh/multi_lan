#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Якщо subdomain_prefix є NULL або порожнім, повертаємо базовий домен
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(strlen(domain) + 8); // 8 для "https://" та '\0'
        if (url != NULL) {
            sprintf(url, "https://%s", domain);
        }
        return url;
    }

    // Перевірка на валідність субдомену - він не повинен містити пробілів
    if (strchr(subdomain_prefix, ' ') != NULL) {
        return NULL; // повертаємо NULL, якщо субдомен недійсний
    }

    // Формування URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}