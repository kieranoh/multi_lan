#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Controleer op NULL pointers
    if (target == NULL || domain == NULL) {
        char* fallback = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // Controleer of target begint met "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Target begint niet met https://, gebruik domein als fallback
        char* fallback = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (fallback == NULL) return NULL;
        sprintf(fallback, "https://%s", domain);
        return fallback;
    }
    
    // Haal het hostgedeelte uit de target URL
    const char* host_start = target + https_len;
    
    // Zoek naar het eerste '/' na het protocol om het hostgedeelte te isoleren
    const char* path_start = strchr(host_start, '/');
    size_t host_length;
    
    if (path_start == NULL) {
        // Geen pad gevonden, hele string na https:// is host
        host_length = strlen(host_start);
    } else {
        host_length = path_start - host_start;
    }
    
    // Controleer of het domein voorkomt aan het einde van de host
    size_t domain_len = strlen(domain);
    
    if (host_length >= domain_len) {
        // Controleer of de host eindigt op het domein
        const char* host_end = host_start + host_length;
        const char* domain_match_start = host_end - domain_len;
        
        // Controleer exacte match van domein
        if (strcmp(domain_match_start, domain) == 0) {
            // Controleer of het domein het hele hostgedeelte is, of een subdomein
            if (host_length == domain_len || 
                (domain_match_start > host_start && *(domain_match_start - 1) == '.')) {
                // Target valt binnen het domein, retourneer een kopie van target
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) return NULL;
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // Target valt niet binnen het domein, gebruik domein als fallback
    char* fallback = (char*)malloc(strlen("https://") + strlen(domain) + 1);
    if (fallback == NULL) return NULL;
    sprintf(fallback, "https://%s", domain);
    return fallback;
}