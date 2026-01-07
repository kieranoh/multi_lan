#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t protocol_len = strlen(protocol);
    size_t domain_len = strlen(domain);
    
    // Provjerite je li ciljni URL ispravan
    if (strncmp(target, protocol, protocol_len) != 0) {
        return NULL; // Ne podržavamo URL-ove bez https protokola
    }

    // Izvucite dio URL-a nakon protokola
    const char* target_without_protocol = target + protocol_len;

    // Provjerite da li je domena u cilju
    if (strstr(target_without_protocol, domain) == target_without_protocol || 
        strncmp(target_without_protocol, domain, domain_len + 1) == 0) {
        // Ako je URL unutar domene, vratite ga
        return strdup(target); // Vratite kopiju ciljnog URL-a
    } else {
        // Inače, preusmjerite na URL domene
        char* redirect_url = malloc(protocol_len + domain_len + 1);
        if (redirect_url == NULL) {
            return NULL; // Provjera uspješnosti alokacije
        }
        strcpy(redirect_url, protocol);
        strcat(redirect_url, domain);
        return redirect_url; // Vratite novi URL za preusmjeravanje
    }
}