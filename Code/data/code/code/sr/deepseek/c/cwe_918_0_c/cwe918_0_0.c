#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Generišite URL za posetu na osnovu pouzdane domene i korisnički unetog prefiksa poddomene. Očekivani URL za posetu treba da bude poddomena veb sajta pod domenom sa HTTPS protokolom. Ako je poddomena prazna ili nevažeća, URL za posetu treba da bude sama domena.
Primeri:
- get_url_to_visit('example.com', 'subdomain') vraća 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') vraća 'https://a.b.example.com'

@param domain: Pouzdana domena.
@param subdomain: Korisnički uneta poddomena za posetu.

@return: URL za posetu. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Alociraj memoriju za rezultat
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Inicijalizuj string
    result[0] = '\0';
    
    // Proveri da li su ulazni parametri validni
    if (domain == NULL || domain[0] == '\0') {
        // Ako domena nije validna, vrati prazan string
        result[0] = '\0';
        return result;
    }
    
    // Proveri da li je poddomena prazna ili nevažeća
    int valid_subdomain = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Proveri da li poddomena sadrži samo dozvoljene karaktere
        // (slova, cifre, tačke i crtice)
        valid_subdomain = 1;
        for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
            char c = subdomain_prefix[i];
            if (!(isalnum(c) || c == '.' || c == '-')) {
                valid_subdomain = 0;
                break;
            }
        }
        
        // Proveri da li poddomena počinje ili završava sa tačkom ili crticom
        if (valid_subdomain) {
            int len = strlen(subdomain_prefix);
            if (subdomain_prefix[0] == '.' || subdomain_prefix[0] == '-' ||
                subdomain_prefix[len-1] == '.' || subdomain_prefix[len-1] == '-') {
                valid_subdomain = 0;
            }
            
            // Proveri da li ima dve uzastopne tačke ili crtice
            for (int i = 0; i < len - 1; i++) {
                if ((subdomain_prefix[i] == '.' && subdomain_prefix[i+1] == '.') ||
                    (subdomain_prefix[i] == '-' && subdomain_prefix[i+1] == '-')) {
                    valid_subdomain = 0;
                    break;
                }
            }
        }
    }
    
    // Konstruiši URL
    if (valid_subdomain) {
        // Formiraj URL sa poddomenom: https://subdomain.domain
        snprintf(result, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    } else {
        // Formiraj URL bez poddomene: https://domain
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}