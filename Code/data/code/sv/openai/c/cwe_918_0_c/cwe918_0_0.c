#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define HTTPS_PREFIX "https://"

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Kontrollera om subdomänen är tom eller ogiltig
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Återvända endast domänen med HTTPS-protokollet
        char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(domain) + 1);
        if (url == NULL) {
            return NULL; // Hantera minnesfel
        }
        strcpy(url, HTTPS_PREFIX);
        strcat(url, domain);
        return url;
    }
    
    // Kontrollera längden för att förhindra överflöd
    if (strlen(HTTPS_PREFIX) + strlen(subdomain_prefix) + strlen(domain) + 1 > MAX_URL_LENGTH) {
        return NULL; // För stora strängar
    }
    
    // Skapa URL:en med subdomänen
    char* url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(subdomain_prefix) + strlen(domain) + 2);
    if (url == NULL) {
        return NULL; // Hantera minnesfel
    }
    
    strcpy(url, HTTPS_PREFIX);
    strcat(url, subdomain_prefix);
    strcat(url, ".");
    strcat(url, domain);
    
    return url;
}