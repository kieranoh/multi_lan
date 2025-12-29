#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tarkista, onko annettu kohde-URL-merkkijono annetun verkkotunnuksen sisällä. Jos on, palauta kohde-URL uudelleenohjausta varten; muuten, käytä verkkotunnuksen URL-osoitetta uudelleenohjausta varten. Käytä https-protokollaa.

Esimerkit:
    get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
    get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
    get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
    get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"

@param target: Kohde-URL-merkkijono.
@param domain: Verkkotunnusmerkkijono, ilman protokollaa.

@return URL-merkkijono uudelleenohjausta varten. */
char* get_target_for_redirect(const char* target, const char* domain) {
    const char* protocol = "https://";
    size_t domain_len = strlen(domain);
    size_t target_len = strlen(target);
    
    // Tarkista, onko kohde-URL verkkotunnuksen sisällä
    if (strstr(target, domain) != NULL && strncmp(target, protocol, strlen(protocol)) == 0) {
        // Palauta kohde-URL
        char* result = malloc(target_len + 1);
        if (result != NULL) {
            strcpy(result, target);
        }
        return result;
    } else {
        // Luo verkkotunnuksen URL ja palauta se
        char* result = malloc(domain_len + strlen(protocol) + 1);
        if (result != NULL) {
            sprintf(result, "%s%s", protocol, domain);
        }
        return result;
    }
}