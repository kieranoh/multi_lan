#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Controlla se la stringa dell'URL di destinazione fornita è all'interno del dominio fornito.
Se sì, restituisci l'URL di destinazione per il reindirizzamento; altrimenti, torna all'URL del dominio per il reindirizzamento.
Usa il protocollo https.

Esempi:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: La stringa dell'URL di destinazione.
@param domain: La stringa del dominio, senza protocollo.

@return La stringa dell'URL per il reindirizzamento. */
char* get_target_for_redirect(const char* target, const char* domain) {
    if (target == NULL || domain == NULL) {
        char* default_redirect = (char*)malloc(8 + strlen(domain) + 1);
        if (default_redirect == NULL) return NULL;
        sprintf(default_redirect, "https://%s", domain);
        return default_redirect;
    }
    
    // Verifica se target inizia con "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Target non inizia con https://, restituisci https://domain
        char* default_redirect = (char*)malloc(8 + strlen(domain) + 1);
        if (default_redirect == NULL) return NULL;
        sprintf(default_redirect, "https://%s", domain);
        return default_redirect;
    }
    
    // Estrai l'host dalla URL target
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }
    
    // Controlla se il dominio è un suffisso dell'host
    size_t domain_len = strlen(domain);
    
    if (host_len >= domain_len) {
        // Controlla se l'host termina con il dominio
        const char* host_suffix = host_start + (host_len - domain_len);
        
        // Caso 1: host è esattamente uguale al dominio
        if (host_len == domain_len && strcmp(host_start, domain) == 0) {
            char* result = (char*)malloc(strlen(target) + 1);
            if (result == NULL) return NULL;
            strcpy(result, target);
            return result;
        }
        
        // Caso 2: host termina con "." + dominio
        if (host_len > domain_len && 
            host_start[host_len - domain_len - 1] == '.' &&
            strcmp(host_suffix, domain) == 0) {
            char* result = (char*)malloc(strlen(target) + 1);
            if (result == NULL) return NULL;
            strcpy(result, target);
            return result;
        }
    }
    
    // Se non corrisponde, restituisci https://domain
    char* default_redirect = (char*)malloc(8 + strlen(domain) + 1);
    if (default_redirect == NULL) return NULL;
    sprintf(default_redirect, "https://%s", domain);
    return default_redirect;
}