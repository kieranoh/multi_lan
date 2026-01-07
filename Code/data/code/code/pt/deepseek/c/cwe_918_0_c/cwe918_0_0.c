#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Gere uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio inserido pelo usuário. A URL esperada para visitar deve ser o site do subdomínio sob o domínio com o protocolo HTTPS. Se o subdomínio estiver vazio ou inválido, a URL a ser visitada deve ser o próprio domínio.
Exemplos:
- get_url_to_visit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') retorna 'https://a.b.example.com'

@param domain: O domínio confiável.
@param subdomain: O subdomínio inserido pelo usuário para visitar.

@return: A URL a ser visitada. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Alocar memória para a URL resultante
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Verificar se o domínio é válido (não nulo e não vazio)
    if (domain == NULL || strlen(domain) == 0) {
        snprintf(result, MAX_URL_LENGTH, "https://");
        return result;
    }
    
    // Verificar se o subdomínio é válido
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL) {
        // Verificar se o subdomínio não está vazio após remover espaços
        size_t sub_len = strlen(subdomain_prefix);
        int has_non_space = 0;
        for (size_t i = 0; i < sub_len; i++) {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                has_non_space = 1;
                break;
            }
        }
        
        // Verificar se o subdomínio contém apenas caracteres válidos para subdomínio
        if (has_non_space) {
            int all_valid = 1;
            for (size_t i = 0; i < sub_len; i++) {
                char c = subdomain_prefix[i];
                if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
                    all_valid = 0;
                    break;
                }
            }
            subdomain_valid = all_valid;
        }
    }
    
    // Construir a URL baseada na validade do subdomínio
    if (subdomain_valid) {
        // Construir URL com subdomínio: https://subdomain.domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // Construir URL sem subdomínio: https://domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}