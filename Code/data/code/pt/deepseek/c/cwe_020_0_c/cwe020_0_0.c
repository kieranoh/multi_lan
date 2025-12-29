#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Verifique se a string da URL de destino fornecida está dentro do domínio fornecido.
Se sim, retorne a URL de destino para redirecionamento; caso contrário, volte para a URL do domínio para redirecionamento.
Use o protocolo https.

Exemplos:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: A string da URL de destino.
@param domain: A string do domínio, sem protocolo.

@return A string da URL para redirecionamento. */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Verificar entradas nulas
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain ? domain : "example.com") + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain ? domain : "example.com");
        return default_url;
    }
    
    // Verificar se a URL de destino começa com "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Se não começar com https://, retornar o domínio com https
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // Extrair o host da URL de destino
    const char* host_start = target + https_len;
    const char* host_end = strchr(host_start, '/');
    
    size_t host_len;
    if (host_end == NULL) {
        host_len = strlen(host_start);
    } else {
        host_len = host_end - host_start;
    }
    
    // Verificar se o domínio está contido no host
    size_t domain_len = strlen(domain);
    
    // Caso 1: host é exatamente igual ao domínio
    if (host_len == domain_len && strncmp(host_start, domain, host_len) == 0) {
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    }
    
    // Caso 2: host termina com "." + domínio (subdomínio válido)
    if (host_len > domain_len + 1 && 
        host_start[host_len - domain_len - 1] == '.' &&
        strncmp(host_start + host_len - domain_len, domain, domain_len) == 0) {
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    }
    
    // Caso contrário, retornar o domínio com https
    char* result = (char*)malloc(https_len + strlen(domain) + 1);
    if (result == NULL) return NULL;
    sprintf(result, "%s%s", https_prefix, domain);
    return result;
}