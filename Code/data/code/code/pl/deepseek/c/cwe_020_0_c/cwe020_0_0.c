#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Sprawdza, czy podany ciąg URL docelowego znajduje się w podanej domenie.
 * Jeśli tak, zwraca URL docelowy do przekierowania; w przeciwnym razie, przechodzi do URL domeny do przekierowania.
 * Używa protokołu https.
 *
 * @param target: Ciąg URL docelowego.
 * @param domain: Ciąg domeny, bez protokołu.
 * @return Ciąg URL do przekierowania (należy zwolnić pamięć po użyciu).
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Sprawdzenie poprawności parametrów wejściowych
    if (target == NULL || domain == NULL) {
        char* default_result = (char*)malloc(8 + strlen(domain ? domain : "example.com") + 1);
        if (default_result == NULL) return NULL;
        sprintf(default_result, "https://%s", domain ? domain : "example.com");
        return default_result;
    }
    
    // Sprawdzenie, czy target zaczyna się od "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Jeśli target nie zaczyna się od https://, zwracamy domenę z https://
        char* result = (char*)malloc(https_len + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "%s%s", https_prefix, domain);
        return result;
    }
    
    // Pobranie części hosta z target URL (po "https://")
    const char* target_host = target + https_len;
    
    // Znalezienie końca hosta (przed pierwszą kreską '/' lub końcem stringa)
    const char* host_end = target_host;
    while (*host_end != '\0' && *host_end != '/' && *host_end != ':' && *host_end != '?') {
        host_end++;
    }
    
    // Sprawdzenie, czy host kończy się domeną
    size_t host_len = host_end - target_host;
    size_t domain_len = strlen(domain);
    
    // Sprawdzenie, czy host jest dokładnie równy domenie
    if (host_len == domain_len && strncmp(target_host, domain, host_len) == 0) {
        // Host jest dokładnie równy domenie
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    }
    
    // Sprawdzenie, czy host kończy się domeną (np. "music.example.com" kończy się na "example.com")
    if (host_len > domain_len + 1) {  // +1 dla kropki
        // Sprawdzenie, czy host kończy się na ".domain"
        if (target_host[host_len - domain_len - 1] == '.' && 
            strncmp(target_host + host_len - domain_len, domain, domain_len) == 0) {
            // Host kończy się na domenie
            char* result = (char*)malloc(strlen(target) + 1);
            if (result == NULL) return NULL;
            strcpy(result, target);
            return result;
        }
    }
    
    // Jeśli nie pasuje, zwracamy domenę z https://
    char* result = (char*)malloc(https_len + strlen(domain) + 1);
    if (result == NULL) return NULL;
    sprintf(result, "%s%s", https_prefix, domain);
    return result;
}