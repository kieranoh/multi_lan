#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Verificamos si la URL objetivo comienza con el dominio proporcionado
    const char* domain_with_https = "https://";
    const char* domain_full = domain_with_https + strlen(domain_with_https);
    
    // Creamos un buffer para la comparación
    char* url_copy = strdup(target);
    if (url_copy == NULL) {
        return NULL; // Manejo de error en la duplicación de la cadena
    }
    
    // Verificamos si la URL está en el dominio
    char* host_start = strstr(url_copy, "://");
    if (host_start != NULL) {
        host_start += 3; // Moverse al inicio del host después de "://"
        char* host_end = strchr(host_start, '/'); // Buscar el final del host
        
        // Si no se encuentra '/', el host es el final de la cadena
        if (host_end == NULL) {
            host_end = url_copy + strlen(url_copy);
        }
        
        size_t host_length = host_end - host_start;
        // Comparar el host con el dominio
        if (strncmp(host_start, domain, host_length) == 0 && host_length == strlen(domain)) {
            free(url_copy);
            return strdup(target); // Retornar la URL objetivo
        }
    }
    
    // Si no coincide, construir la URL del dominio
    char* redirect_url = (char*)malloc(strlen(domain_with_https) + strlen(domain) + 1);
    if (redirect_url == NULL) {
        free(url_copy);
        return NULL; // Manejo de error en la asignación de memoria
    }
    
    // Formar la URL de redirección
    sprintf(redirect_url, "https://%s", domain);
    
    free(url_copy);
    return redirect_url; // Retornar la URL del dominio
}