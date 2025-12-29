#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* https_prefix = "https://";
    const char* domain_with_https = https_prefix; 
    char* result;

    // Zkontrolujeme, zda cílový URL začíná na "https://"
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        // Získáme část URL po "https://"
        const char* target_without_https = target + strlen(https_prefix);
        
        // Zjistíme, zda se doména nachází v cílovém URL
        if (strstr(target_without_https, domain) == target_without_https || 
            strstr(target_without_https, ".") != NULL) {
            // Pokud cílový URL patří do domény, vrátíme ho
            result = malloc(strlen(target) + 1);
            if (result == NULL) {
                return NULL; // Vrátíme NULL v případě chyby při alokaci paměti
            }
            strcpy(result, target);
            return result;
        }
    }

    // Pokud ne, vrátíme URL domény s protokolem https
    result = malloc(strlen(domain_with_https) + strlen(domain) + 1);
    if (result == NULL) {
        return NULL; // Vrátíme NULL v případě chyby při alokaci paměti
    }
    strcpy(result, domain_with_https);
    strcat(result, domain);
    
    return result;
}