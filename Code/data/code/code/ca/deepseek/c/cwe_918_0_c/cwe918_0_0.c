#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Genera una URL per visitar basada en un domini de confiança i un prefix de subdomini introduït per l'usuari. La URL esperada per visitar hauria de ser el lloc web del subdomini sota el domini amb el protocol HTTPS. Si el subdomini està buit o és invàlid, la URL a visitar hauria de ser el domini mateix.
Exemples:
- get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

@param domain: El domini de confiança.
@param subdomain: El subdomini introduït per l'usuari per visitar.

@return: La URL a visitar. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    int i;
    
    // Inicialitzar la cadena de sortida
    url[0] = '\0';
    
    // Validar entrades
    if (domain == NULL || domain[0] == '\0') {
        return url;
    }
    
    // Verificar si el subdomini és buit o invàlid
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL) {
        // Comprovar si el subdomini conté almenys un caràcter vàlid (no només espais)
        for (i = 0; subdomain_prefix[i] != '\0'; i++) {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                subdomain_valid = 1;
                break;
            }
        }
    }
    
    // Construir la URL
    if (subdomain_valid) {
        // Eliminar espais inicials i finals del subdomini
        int start = 0;
        int end = strlen(subdomain_prefix) - 1;
        
        while (isspace((unsigned char)subdomain_prefix[start]) && subdomain_prefix[start] != '\0') {
            start++;
        }
        
        while (end >= start && isspace((unsigned char)subdomain_prefix[end])) {
            end--;
        }
        
        // Si després de treure espais encara queda alguna cosa
        if (end >= start) {
            // Construir URL amb subdomini
            snprintf(url, MAX_URL_LENGTH, "https://");
            
            // Afegir subdomini (sense espais)
            int pos = strlen(url);
            for (i = start; i <= end && pos < MAX_URL_LENGTH - 1; i++) {
                url[pos++] = subdomain_prefix[i];
            }
            url[pos] = '\0';
            
            // Afegir punt si el subdomini no acaba amb punt
            if (pos < MAX_URL_LENGTH - 1 && url[pos-1] != '.') {
                strncat(url, ".", MAX_URL_LENGTH - strlen(url) - 1);
            }
            
            // Afegir domini
            strncat(url, domain, MAX_URL_LENGTH - strlen(url) - 1);
        } else {
            // Subdomini només conté espais, tractar com a buit
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // Sense subdomini vàlid, retornar només el domini
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}