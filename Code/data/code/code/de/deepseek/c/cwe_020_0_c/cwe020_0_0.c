#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Überprüft, ob eine URL innerhalb einer bestimmten Domain liegt.
 * 
 * @param target Die Ziel-URL-Zeichenfolge.
 * @param domain Die Domain-Zeichenfolge, ohne Protokoll.
 * @return Die URL-Zeichenfolge für die Weiterleitung.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Konstante für das HTTPS-Protokoll
    const char* HTTPS_PREFIX = "https://";
    const int HTTPS_PREFIX_LEN = 8;
    
    // Fallback-URL erstellen
    char* fallback_url = (char*)malloc(strlen(HTTPS_PREFIX) + strlen(domain) + 1);
    if (!fallback_url) {
        return NULL;
    }
    sprintf(fallback_url, "%s%s", HTTPS_PREFIX, domain);
    
    // Prüfen, ob target mit "https://" beginnt
    if (strncmp(target, HTTPS_PREFIX, HTTPS_PREFIX_LEN) != 0) {
        // target beginnt nicht mit https://, Fallback verwenden
        return fallback_url;
    }
    
    // Domain aus der target-URL extrahieren
    const char* target_after_protocol = target + HTTPS_PREFIX_LEN;
    
    // Finde das Ende der Domain (ersten '/' oder String-Ende)
    const char* domain_end = target_after_protocol;
    while (*domain_end && *domain_end != '/' && *domain_end != ':') {
        domain_end++;
    }
    
    // Länge der Domain in der target-URL berechnen
    size_t target_domain_len = domain_end - target_after_protocol;
    
    // Prüfen, ob die Domain in target mit der angegebenen Domain übereinstimmt
    int domain_match = 0;
    
    // Fall 1: Exakte Übereinstimmung
    if (strlen(domain) == target_domain_len && 
        strncmp(target_after_protocol, domain, target_domain_len) == 0) {
        domain_match = 1;
    }
    // Fall 2: Subdomain (target-Domain endet mit "." + domain)
    else if (target_domain_len > strlen(domain) + 1) {
        size_t dot_position = target_domain_len - strlen(domain) - 1;
        if (target_after_protocol[dot_position] == '.' &&
            strncmp(target_after_protocol + dot_position + 1, domain, strlen(domain)) == 0) {
            domain_match = 1;
        }
    }
    
    if (domain_match) {
        // Domain stimmt überein, originale target-URL zurückgeben
        free(fallback_url);
        char* result = (char*)malloc(strlen(target) + 1);
        if (!result) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // Domain stimmt nicht überein, Fallback zurückgeben
        return fallback_url;
    }
}