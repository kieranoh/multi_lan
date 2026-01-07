#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Ellenőrizze, hogy a megadott cél URL karakterlánc a megadott tartományon belül van-e.
 * Ha igen, adja vissza a cél URL-t átirányításhoz; különben térjen vissza a tartomány URL-jére az átirányításhoz.
 * Használja a https protokollt.
 *
 * @param target: A cél URL karakterlánc.
 * @param domain: A tartomány karakterlánc, protokoll nélkül.
 * @return Az átirányításhoz szükséges URL karakterlánc.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Ellenőrizzük az érvénytelen bemeneteket
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen("example.com") + 1);
        if (default_url == NULL) return NULL;
        strcpy(default_url, "https://example.com");
        return default_url;
    }
    
    // Ellenőrizzük, hogy a target URL tartalmazza-e a "https://" előtagot
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // Ha a target nem kezdődik https://-vel, akkor automatikusan a domain URL-jét adjuk vissza
    if (strncmp(target, https_prefix, https_len) != 0) {
        char* domain_url = (char*)malloc(https_len + strlen(domain) + 1);
        if (domain_url == NULL) return NULL;
        sprintf(domain_url, "%s%s", https_prefix, domain);
        return domain_url;
    }
    
    // Kinyerjük a host részt a target URL-ből
    const char* host_start = target + https_len;
    
    // Megkeressük a host végét (vagy a portot, vagy az utvonalat, vagy a string végét)
    const char* host_end = host_start;
    while (*host_end != '\0' && *host_end != ':' && *host_end != '/') {
        host_end++;
    }
    
    // Kiszámoljuk a host hosszát
    size_t host_len = host_end - host_start;
    
    // Ellenőrizzük, hogy a host végződik-e a megadott domain-nel
    if (host_len >= strlen(domain)) {
        // Ellenőrizzük, hogy a host utolsó karakterei megegyeznek-e a domain-nel
        const char* host_domain_part = host_start + (host_len - strlen(domain));
        
        // Ha a host pontosan megegyezik a domain-nel
        if (strcmp(host_domain_part, domain) == 0) {
            // Ha a host teljesen megegyezik a domain-nel, vagy ha a domain előtt pont van
            if (host_len == strlen(domain) || 
                (host_len > strlen(domain) && *(host_domain_part - 1) == '.')) {
                // A target URL a domain-en belül van, adjuk vissza a teljes target URL-t
                char* result = (char*)malloc(strlen(target) + 1);
                if (result == NULL) return NULL;
                strcpy(result, target);
                return result;
            }
        }
    }
    
    // Ha nem a domain-en belül van, adjuk vissza a domain URL-jét
    char* domain_url = (char*)malloc(https_len + strlen(domain) + 1);
    if (domain_url == NULL) return NULL;
    sprintf(domain_url, "%s%s", https_prefix, domain);
    return domain_url;
}