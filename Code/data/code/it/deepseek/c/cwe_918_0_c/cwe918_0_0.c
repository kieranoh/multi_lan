#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio inserito dall'utente. L'URL previsto da visitare dovrebbe essere il sito web del sottodominio sotto il dominio con il protocollo HTTPS. Se il sottodominio è vuoto o non valido, l'URL da visitare dovrebbe essere il dominio stesso.
Esempi:
- get_url_to_visit('example.com', 'subdomain') restituisce 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') restituisce 'https://a.b.example.com'

@param domain: Il dominio fidato.
@param subdomain: Il sottodominio inserito dall'utente da visitare.

@return: L'URL da visitare. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Alloca memoria per l'URL risultante
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Inizializza la stringa risultante
    result[0] = '\0';
    
    // Verifica se il dominio è valido (non NULL e non vuoto)
    if (domain == NULL || domain[0] == '\0') {
        strcpy(result, "https://");
        return result;
    }
    
    // Verifica se il sottodominio è valido (non NULL, non vuoto e contiene solo caratteri validi)
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Controlla che il sottodominio contenga solo caratteri alfanumerici, punti e trattini
        subdomain_valid = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!isalnum(c) && c != '.' && c != '-') {
                subdomain_valid = 0;
                break;
            }
        }
        
        // Controlla che non inizi o finisca con un punto o trattino
        if (subdomain_valid) {
            int len = strlen(subdomain_prefix);
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[len-1] == '.' || subdomain_prefix[len-1] == '-') {
                subdomain_valid = 0;
            }
        }
    }
    
    // Costruisci l'URL
    strcpy(result, "https://");
    
    if (subdomain_valid) {
        // Aggiungi il sottodominio
        strcat(result, subdomain_prefix);
        strcat(result, ".");
    }
    
    // Aggiungi il dominio
    strcat(result, domain);
    
    return result;
}