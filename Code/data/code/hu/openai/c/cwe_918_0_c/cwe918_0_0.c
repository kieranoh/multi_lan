#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Ellenőrizzük, hogy a domain érvényes-e
    if (domain == NULL || strlen(domain) == 0) {
        return NULL; // Érvénytelen domain esetén visszatérünk NULL-lal
    }

    // Ellenőrizzük, hogy a subdomain_prefix érvényes-e
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Ha üres az aldomain, az URL a domain lesz
        char* url = (char*)malloc(strlen(domain) + 8); // 'https://' + domain + '\0'
        if (url == NULL) {
            return NULL; // Memóriaallokációs hiba
        }
        sprintf(url, "https://%s", domain);
        return url;
    }

    // Ellenőrizzük a subdomain_prefix érvényességét (csak alfanumerikus karakterek és pontok)
    for (const char* p = subdomain_prefix; *p != '\0'; p++) {
        if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || 
               (*p >= '0' && *p <= '9') || *p == '.')) {
            return NULL; // Érvénytelen aldomain esetén visszatérünk NULL-lal
        }
    }

    // Összeállítjuk a végső URL-t
    char* url = (char*)malloc(strlen(domain) + strlen(subdomain_prefix) + 9); // 'https://' + subdomain + '.' + domain + '\0'
    if (url == NULL) {
        return NULL; // Memóriaallokációs hiba
    }

    sprintf(url, "https://%s.%s", subdomain_prefix, domain);
    return url;
}