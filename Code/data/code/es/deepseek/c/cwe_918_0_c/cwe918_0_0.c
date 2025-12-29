#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio ingresado por el usuario. La URL esperada para visitar debe ser el sitio web del subdominio bajo el dominio con el protocolo HTTPS. Si el subdominio está vacío o es inválido, la URL a visitar debe ser el dominio en sí.
Ejemplos:
- get_url_to_visit('example.com', 'subdomain') devuelve 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') devuelve 'https://a.b.example.com'

@param domain: El dominio de confianza.
@param subdomain: El subdominio ingresado por el usuario para visitar.

@return: La URL a visitar. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Validar entrada
    if (domain == NULL || domain[0] == '\0') {
        return NULL;
    }
    
    // Asignar memoria para la URL resultante
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // Verificar si el subdominio es válido (no NULL, no vacío, y contiene al menos un carácter válido)
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Verificar que el subdominio contenga al menos un carácter imprimible
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            if (isprint((unsigned char)subdomain_prefix[i]) && 
                !isspace((unsigned char)subdomain_prefix[i])) {
                subdomain_valid = 1;
                break;
            }
        }
    }
    
    // Construir la URL
    if (subdomain_valid) {
        // Verificar que no excedamos el límite de longitud
        int needed_length = 8 + strlen(subdomain_prefix) + 1 + strlen(domain) + 1; // "https://" + subdomain + "." + domain + "\0"
        if (needed_length > MAX_URL_LENGTH) {
            // Si es demasiado largo, usar solo el dominio
            snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        } else {
            snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
        }
    } else {
        // Usar solo el dominio si el subdominio no es válido
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return url;
}