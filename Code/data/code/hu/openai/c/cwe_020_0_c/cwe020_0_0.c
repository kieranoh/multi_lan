#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t protocol_length = strlen(protocol);
    size_t domain_length = strlen(domain);
    
    // Ellenőrizzük, hogy a cél URL a megadott tartományon belül van-e
    if (strncmp(target, protocol, protocol_length) == 0) {
        const char* domain_start = target + protocol_length;
        if (strncmp(domain_start, domain, domain_length) == 0) {
            // A cél URL a tartományon belül van, visszaadjuk azt
            char* result = (char*)malloc(strlen(target) + 1);
            if (result) {
                strcpy(result, target);
            }
            return result;
        }
    }
    
    // Ha nem a tartományon belül van, visszaadjuk a tartomány URL-jét
    char* result = (char*)malloc(protocol_length + domain_length + 1);
    if (result) {
        strcpy(result, protocol);
        strcat(result, domain);
    }
    return result;
}