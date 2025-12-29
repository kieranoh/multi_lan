#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Verificar entradas nulas
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(strlen("https://") + strlen(domain ? domain : "") + 1);
        if (default_url == NULL) return NULL;
        if (domain) {
            sprintf(default_url, "https://%s", domain);
        } else {
            strcpy(default_url, "https://");
        }
        return default_url;
    }
    
    // Extraer el hostname del target
    const char* protocol_prefix = "https://";
    const char* hostname_start = target;
    
    // Saltar el protocolo si está presente
    if (strncmp(target, protocol_prefix, strlen(protocol_prefix)) == 0) {
        hostname_start = target + strlen(protocol_prefix);
    }
    
    // Encontrar el final del hostname (antes de '/' o fin de cadena)
    const char* hostname_end = hostname_start;
    while (*hostname_end != '\0' && *hostname_end != '/' && *hostname_end != ':' && *hostname_end != '?') {
        hostname_end++;
    }
    
    // Extraer el hostname
    int hostname_len = hostname_end - hostname_start;
    char* hostname = (char*)malloc(hostname_len + 1);
    if (hostname == NULL) return NULL;
    strncpy(hostname, hostname_start, hostname_len);
    hostname[hostname_len] = '\0';
    
    // Verificar si el hostname termina con el dominio
    int domain_len = strlen(domain);
    int hostname_len_full = strlen(hostname);
    
    int is_same_domain = 0;
    
    // Caso 1: El hostname es exactamente igual al dominio
    if (strcmp(hostname, domain) == 0) {
        is_same_domain = 1;
    }
    // Caso 2: El hostname termina con .domain
    else if (hostname_len_full > domain_len + 1 && 
             hostname[hostname_len_full - domain_len - 1] == '.' &&
             strcmp(hostname + hostname_len_full - domain_len, domain) == 0) {
        is_same_domain = 1;
    }
    
    free(hostname);
    
    // Si es el mismo dominio, retornar el target original (asegurando que tenga https)
    if (is_same_domain) {
        // Verificar si el target ya comienza con https://
        if (strncmp(target, "https://", 8) == 0) {
            char* result = (char*)malloc(strlen(target) + 1);
            if (result == NULL) return NULL;
            strcpy(result, target);
            return result;
        } else {
            // Si no tiene https://, agregarlo
            char* result = (char*)malloc(strlen("https://") + strlen(target) + 1);
            if (result == NULL) return NULL;
            sprintf(result, "https://%s", target);
            return result;
        }
    } else {
        // Si no es el mismo dominio, retornar https:// + domain
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "https://%s", domain);
        return result;
    }
}