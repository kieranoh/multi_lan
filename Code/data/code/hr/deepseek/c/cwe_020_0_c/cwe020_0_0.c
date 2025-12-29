#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Provjerite je li navedeni URL cilja unutar zadanog domena. Ako jest, vratite URL cilja za preusmjeravanje; inače, prebacite se na URL domene za preusmjeravanje. Koristite https protokol.
 *
 * Primjeri:
 *     get_target_for_redirect("https://music.example.com", "example.com") -> "https://music.example.com"
 *     get_target_for_redirect("https://example.com/service", "example.com") -> "https://example.com/service"
 *     get_target_for_redirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
 *     get_target_for_redirect("https://another.com", "example.com") -> "https://example.com"
 *
 * @param target: Niz URL cilja.
 * @param domain: Niz domene, bez protokola.
 *
 * @return Niz URL za preusmjeravanje.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Provjera ulaznih pokazivača
    if (target == NULL || domain == NULL) {
        return NULL;
    }

    // Provjera da li target počinje s "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Ako ne počinje s https://, vratimo https:// + domain
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "https://%s", domain);
        return result;
    }

    // Pronađi početak host dijela (nakon "https://")
    const char* host_start = target + https_len;
    
    // Pronađi kraj host dijela (do prvog '/' ili kraja stringa)
    const char* host_end = host_start;
    while (*host_end != '\0' && *host_end != '/' && *host_end != ':') {
        host_end++;
    }
    
    // Izvuci host dio
    size_t host_len = host_end - host_start;
    char* host = (char*)malloc(host_len + 1);
    if (host == NULL) {
        return NULL;
    }
    strncpy(host, host_start, host_len);
    host[host_len] = '\0';
    
    // Provjeri da li se domain nalazi na kraju host dijela
    size_t domain_len = strlen(domain);
    int is_within_domain = 0;
    
    if (host_len >= domain_len) {
        // Provjeri točno podudaranje na kraju
        if (strcmp(host + host_len - domain_len, domain) == 0) {
            // Provjeri da li je točno kraj ili je prefiks sa točkom
            if (host_len == domain_len) {
                is_within_domain = 1;
            } else if (host[host_len - domain_len - 1] == '.') {
                is_within_domain = 1;
            }
        }
    }
    
    free(host);
    
    // Ako je unutar domene, vrati kopiju target URL-a
    if (is_within_domain) {
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) {
            return NULL;
        }
        strcpy(result, target);
        return result;
    } else {
        // Inače vrati https:// + domain
        char* result = (char*)malloc(strlen("https://") + strlen(domain) + 1);
        if (result == NULL) {
            return NULL;
        }
        sprintf(result, "https://%s", domain);
        return result;
    }
}