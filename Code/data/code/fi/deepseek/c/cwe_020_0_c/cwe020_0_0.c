#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_target_for_redirect(const char* target, const char* domain) {
    // Tarkista, että syötteet eivät ole NULL
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen(domain) + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
    
    // Tarkista, alkaako kohde-URL "https://"
    if (strncmp(target, "https://", 8) != 0) {
        // Jos ei, käytä verkkotunnuksen URL-osoitetta
        char* default_url = (char*)malloc(8 + strlen(domain) + 1);
        if (default_url == NULL) return NULL;
        sprintf(default_url, "https://%s", domain);
        return default_url;
    }
    
    // Etsi ensimmäinen "/" protokollan jälkeen
    const char* path_start = target + 8; // Siirrytään "https://" jälkeen
    const char* slash_pos = strchr(path_start, '/');
    
    // Päättele hostname
    char hostname[256];
    if (slash_pos != NULL) {
        size_t hostname_len = slash_pos - path_start;
        if (hostname_len >= sizeof(hostname)) {
            hostname_len = sizeof(hostname) - 1;
        }
        strncpy(hostname, path_start, hostname_len);
        hostname[hostname_len] = '\0';
    } else {
        // Ei polkua, koko merkkijono hostname
        strncpy(hostname, path_start, sizeof(hostname) - 1);
        hostname[sizeof(hostname) - 1] = '\0';
    }
    
    // Tarkista, päättyykö hostname annettuun verkkotunnukseen
    size_t hostname_len = strlen(hostname);
    size_t domain_len = strlen(domain);
    
    int is_within_domain = 0;
    
    if (hostname_len == domain_len) {
        // Täsmälleen sama pituus
        if (strcmp(hostname, domain) == 0) {
            is_within_domain = 1;
        }
    } else if (hostname_len > domain_len) {
        // Hostname on pidempi kuin domain
        if (hostname[hostname_len - domain_len - 1] == '.' &&
            strcmp(hostname + (hostname_len - domain_len), domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    // Päätä palautettava URL
    if (is_within_domain) {
        // Palauta alkuperäinen kohde-URL
        char* result = (char*)malloc(strlen(target) + 1);
        if (result == NULL) return NULL;
        strcpy(result, target);
        return result;
    } else {
        // Palauta verkkotunnuksen URL
        char* result = (char*)malloc(8 + strlen(domain) + 1);
        if (result == NULL) return NULL;
        sprintf(result, "https://%s", domain);
        return result;
    }
}