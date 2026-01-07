#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Egiaztatu emandako helburu URL kateak emandako domeinuan dagoen.
 * Horrela bada, itzuli helburu URLa birbideratzeko; bestela, itzuli domeinuko URLa birbideratzeko.
 * Erabili https protokoloa.
 * 
 * @param target: Helburu URL katea.
 * @param domain: Domeinu katea, protokolo barik.
 * @return Birbideratzeko URL katea.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Domeinurako URL osatua sortu
    const char* protocol = "https://";
    size_t domain_len = strlen(domain);
    size_t protocol_len = strlen(protocol);
    
    // Domeinuko URL osatua sortu
    char* domain_url = (char*)malloc(protocol_len + domain_len + 1);
    if (domain_url == NULL) {
        return NULL;
    }
    strcpy(domain_url, protocol);
    strcat(domain_url, domain);
    
    // Helburu URL hutsa edo NULL bada, domeinuko URL itzuli
    if (target == NULL || strlen(target) == 0) {
        return domain_url;
    }
    
    // Helburu URL domeinuan dagoen egiaztatu
    bool is_same_domain = false;
    
    // "https://" hasten den egiaztatu
    if (strncmp(target, protocol, protocol_len) == 0) {
        // Helburu URL domeinuarekin hasten den egiaztatu
        const char* target_after_protocol = target + protocol_len;
        
        // Domeinuaren luzera baino gehiago geratzen bada, domeinuarekin hasten den egiaztatu
        if (strncmp(target_after_protocol, domain, domain_len) == 0) {
            // Domeinuaren ondoren '/' edo '\0' dagoen egiaztatu (azpidomeinuak onartzeko)
            char next_char = target_after_protocol[domain_len];
            if (next_char == '/' || next_char == '\0') {
                is_same_domain = true;
            }
        }
    }
    
    if (is_same_domain) {
        // Helburu URL domeinuan dago, domeinu URL askatu eta helburu URL kopia itzuli
        free(domain_url);
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // Helburu URL ez dago domeinuan, domeinu URL itzuli
        return domain_url;
    }
}