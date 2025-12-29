#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Alokovat paměť pro výsledné URL
    char* result = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    // Inicializovat prázdný řetězec
    result[0] = '\0';
    
    // Kontrola platnosti vstupů
    if (domain == NULL || domain[0] == '\0') {
        // Pokud je doména neplatná, vrátit prázdný řetězec
        return result;
    }
    
    // Zkontrolovat, zda je subdoména prázdná nebo neplatná
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Zkontrolovat, zda obsahuje alespoň jeden netisknutelný znak
        int has_printable = 0;
        for (size_t i = 0; subdomain_prefix[i] != '\0'; i++) {
            if (isprint((unsigned char)subdomain_prefix[i]) && 
                !isspace((unsigned char)subdomain_prefix[i])) {
                has_printable = 1;
                break;
            }
        }
        subdomain_valid = has_printable;
    }
    
    // Sestavit URL
    if (subdomain_valid) {
        // Přidat protokol
        strcat(result, "https://");
        // Přidat subdoménu
        strcat(result, subdomain_prefix);
        // Přidat tečku mezi subdoménu a doménu
        strcat(result, ".");
        // Přidat doménu
        strcat(result, domain);
    } else {
        // Přidat protokol
        strcat(result, "https://");
        // Přidat pouze doménu
        strcat(result, domain);
    }
    
    // Zajistit, aby výsledek nepřekročil maximální délku
    if (strlen(result) >= MAX_URL_LENGTH) {
        result[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return result;
}