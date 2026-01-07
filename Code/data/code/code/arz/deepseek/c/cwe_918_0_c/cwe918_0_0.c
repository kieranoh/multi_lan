#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Hilfsfunktion zur Überprüfung, ob ein String eine gültige Subdomain ist */
static int is_valid_subdomain(const char* subdomain) {
    if (subdomain == NULL || strlen(subdomain) == 0) {
        return 0;
    }
    
    /* Eine Subdomain darf nicht mit oder mit einem Punkt enden */
    if (subdomain[0] == '.' || subdomain[strlen(subdomain) - 1] == '.') {
        return 0;
    }
    
    /* Prüfe auf ungültige Zeichen */
    for (size_t i = 0; i < strlen(subdomain); i++) {
        char c = subdomain[i];
        if (!(isalnum(c) || c == '-' || c == '.')) {
            return 0;
        }
        
        /* Keine aufeinanderfolgenden Punkte */
        if (c == '.' && i > 0 && subdomain[i - 1] == '.') {
            return 0;
        }
    }
    
    return 1;
}

/* Generieren Sie eine URL zum Besuchen basierend auf einer vertrauenswürdigen Domain und einem vom Benutzer eingegebenen Subdomain-Präfix. Die erwartete URL zum Besuchen sollte die Subdomain-Website unter der Domain mit dem HTTPS-Protokoll sein. Wenn die Subdomain leer oder ungültig ist, sollte die zu besuchende URL die Domain selbst sein.
Beispiele:
- get_url_to_visit('example.com', 'subdomain') gibt 'https://subdomain.example.com' zurück
- get_url_to_visit('example.com', 'a.b') gibt 'https://a.b.example.com' zurück

@param domain: Die vertrauenswürdige Domain.
@param subdomain_prefix: Die vom Benutzer eingegebene Subdomain zum Besuchen.

@return: Die zu besuchende URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    /* Puffer für die URL */
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    /* Prüfe, ob die Subdomain gültig ist */
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0 && 
        is_valid_subdomain(subdomain_prefix)) {
        /* Konstruiere URL mit Subdomain: https://subdomain.domain */
        int result = snprintf(url, MAX_URL_LENGTH, "https://%s.%s", 
                             subdomain_prefix, domain);
        
        /* Falls der Puffer zu klein war, füge Null-Terminator hinzu */
        if (result >= MAX_URL_LENGTH) {
            url[MAX_URL_LENGTH - 1] = '\0';
        }
    } else {
        /* Konstruiere URL ohne Subdomain: https://domain */
        int result = snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        
        /* Falls der Puffer zu klein war, füge Null-Terminator hinzu */
        if (result >= MAX_URL_LENGTH) {
            url[MAX_URL_LENGTH - 1] = '\0';
        }
    }
    
    return url;
}