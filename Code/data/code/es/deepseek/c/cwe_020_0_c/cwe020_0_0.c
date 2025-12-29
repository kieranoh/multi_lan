#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
 * Si es así, devuelve la URL objetivo para redirigir; de lo contrario, recurre a la URL del
 * dominio para redirigir. Usa el protocolo https.
 *
 * @param target: La cadena de URL objetivo.
 * @param domain: La cadena de dominio, sin protocolo.
 * @return La cadena de URL para redirigir.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Validación de entrada
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen("example.com") + 1);
        if (default_url != NULL) {
            strcpy(default_url, "https://example.com");
        }
        return default_url;
    }

    // Verificar si target comienza con "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Si no comienza con https://, redirigir al dominio
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }

    // Extraer el host de la URL objetivo
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }

    // Comparar el host con el dominio
    int is_within_domain = 0;
    
    // Caso 1: El host es exactamente igual al dominio
    if (host_len == strlen(domain) && strncmp(host_start, domain, host_len) == 0) {
        is_within_domain = 1;
    }
    // Caso 2: El host termina con "." + dominio (subdominio)
    else if (host_len > strlen(domain) + 1) {
        size_t domain_len = strlen(domain);
        if (host_start[host_len - domain_len - 1] == '.' &&
            strncmp(host_start + host_len - domain_len, domain, domain_len) == 0) {
            is_within_domain = 1;
        }
    }

    if (is_within_domain) {
        // Devolver una copia de la URL objetivo
        char* result = (char*)malloc(strlen(target) + 1);
        if (result != NULL) {
            strcpy(result, target);
        }
        return result;
    } else {
        // Redirigir al dominio principal
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result != NULL) {
            strcpy(result, https_prefix);
            strcat(result, domain);
        }
        return result;
    }
}