#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Kontrollera om måladressen börjar med "https://" 
    const char* https_prefix = "https://";
    size_t domain_length = strlen(domain);
    
    // Skapa en buffert för att lagra den returnerade URL:en
    char* redirect_url = malloc(strlen(target) + 1);
    if (!redirect_url) {
        return NULL; // Hantera minnesallokering
    }
    
    // Kontrollera om måladressen är inom den angivna domänen
    if (strncmp(target, https_prefix, strlen(https_prefix)) == 0) {
        const char* domain_start = target + strlen(https_prefix);
        
        // Kontrollera om måladressen innehåller domänen i början
        if (strncmp(domain_start, domain, domain_length) == 0) {
            strcpy(redirect_url, target);
            return redirect_url; // Returnera måladressen om den är giltig
        }
    }
    
    // Om måladressen inte är inom domänen, returnera domänens URL
    snprintf(redirect_url, strlen(target) + 1, "https://%s", domain);
    return redirect_url;
}