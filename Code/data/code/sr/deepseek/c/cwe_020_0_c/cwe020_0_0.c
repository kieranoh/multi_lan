#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Proverava da li je dati URL cilja unutar datog domena.
 * Ako jeste, vraca URL cilja za preusmeravanje; u suprotnom, prelazi na URL domena za preusmeravanje.
 * Koristi https protokol.
 * 
 * @param target: String URL cilja.
 * @param domain: String domena, bez protokola.
 * @return String URL za preusmeravanje.
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Provera za NULL ulaze
    if (target == NULL || domain == NULL) {
        char* default_redirect = (char*)malloc(20);
        if (default_redirect != NULL) {
            strcpy(default_redirect, "https://");
            strcat(default_redirect, domain ? domain : "");
        }
        return default_redirect;
    }
    
    // Uklanjanje protokola iz target URL-a za poredjenje
    const char* target_without_protocol = target;
    
    // Preskoci "https://" ili "http://" ako postoji
    if (strncmp(target, "https://", 8) == 0) {
        target_without_protocol = target + 8;
    } else if (strncmp(target, "http://", 7) == 0) {
        target_without_protocol = target + 7;
    }
    
    // Pronadji prvi '/' ili kraj stringa
    const char* first_slash = strchr(target_without_protocol, '/');
    size_t hostname_length;
    
    if (first_slash != NULL) {
        hostname_length = first_slash - target_without_protocol;
    } else {
        hostname_length = strlen(target_without_protocol);
    }
    
    // Ekstraktuj hostname iz target URL-a
    char* target_hostname = (char*)malloc(hostname_length + 1);
    if (target_hostname == NULL) {
        return NULL;
    }
    
    strncpy(target_hostname, target_without_protocol, hostname_length);
    target_hostname[hostname_length] = '\0';
    
    // Proveri da li se domena zavrsava sa target_hostname
    int is_within_domain = 0;
    size_t domain_len = strlen(domain);
    size_t target_hostname_len = strlen(target_hostname);
    
    // Proveri da li je target_hostname jednak domenu
    if (strcmp(target_hostname, domain) == 0) {
        is_within_domain = 1;
    }
    // Proveri da li je target_hostname subdomena datog domena
    else if (target_hostname_len > domain_len + 1) {  // +1 za tacku
        // Proveri da li se target_hostname zavrsava sa "." + domain
        if (target_hostname[target_hostname_len - domain_len - 1] == '.' &&
            strcmp(target_hostname + target_hostname_len - domain_len, domain) == 0) {
            is_within_domain = 1;
        }
    }
    
    free(target_hostname);
    
    // Ako je unutar domena, vrati originalni target URL
    if (is_within_domain) {
        // Proveri da li target vec ima https protokol
        if (strncmp(target, "https://", 8) == 0) {
            char* result = (char*)malloc(strlen(target) + 1);
            if (result != NULL) {
                strcpy(result, target);
            }
            return result;
        } else {
            // Dodaj https:// ispred target URL-a
            char* result = (char*)malloc(strlen(target) + 9); // 8 za "https://" + 1 za '\0'
            if (result != NULL) {
                strcpy(result, "https://");
                strcat(result, target_without_protocol);
            }
            return result;
        }
    } else {
        // Nije unutar domena, vrati https:// + domain
        char* result = (char*)malloc(strlen(domain) + 9); // 8 za "https://" + 1 za '\0'
        if (result != NULL) {
            strcpy(result, "https://");
            strcat(result, domain);
        }
        return result;
    }
}