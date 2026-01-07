#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Provjera ulaznih parametara
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }

    // Alokacija memorije za URL
    char* url = (char*)malloc(MAX_URL_LENGTH);
    if (url == NULL) {
        return NULL; // Provjeri je li alokacija uspjela
    }

    // Ako je prefiks poddomene prazan, vraćamo samo domenu
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Provjera je li prefiks poddomene validan (ne smije sadržavati nevažeće znakove)
        if (strchr(subdomain_prefix, '.') != NULL) {
            // Ako je prefiks poddomene validan, generiramo URL
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        } else {
            // Ako nije, vraćamo samo domenu
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
    }

    return url;
}