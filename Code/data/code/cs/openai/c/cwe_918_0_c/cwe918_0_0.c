#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Kontrola platnosti vstupních parametrů
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Pokud je subdoména prázdná nebo neplatná, vracíme pouze doménu
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        char* url = (char*)malloc(strlen(domain) + 8); // 8 pro "https://"
        if (url != NULL) {
            sprintf(url, "https://%s", domain);
        }
        return url;
    }
    
    // Zkontrolujeme, zda subdoména obsahuje neplatné znaky
    for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
        if ((subdomain_prefix[i] < 'a' || subdomain_prefix[i] > 'z') &&
            (subdomain_prefix[i] < 'A' || subdomain_prefix[i] > 'Z') &&
            (subdomain_prefix[i] < '0' || subdomain_prefix[i] > '9') &&
            subdomain_prefix[i] != '.' && subdomain_prefix[i] != '-') {
            return NULL; // Neplatný znak
        }
    }
    
    // Vytvoříme URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url != NULL) {
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    return url;
}