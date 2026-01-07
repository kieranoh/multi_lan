#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Zkontroluje, zda je zadaný cílový URL řetězec v rámci zadané domény.
 *        Pokud ano, vrátí cílový URL pro přesměrování; jinak se přepne na doménový URL pro přesměrování.
 *        Vždy používá protokol https.
 * 
 * @param target Cílový URL řetězec.
 * @param domain Řetězec domény, bez protokolu.
 * @return Řetězec URL pro přesměrování (dynamicky alokovaný - volající zodpovídá za uvolnění).
 */
char* get_target_for_redirect(const char* target, const char* domain) {
    // Kontrola vstupních parametrů
    if (target == NULL || domain == NULL) {
        char* default_url = (char*)malloc(8 + strlen("example.com") + 1);
        if (default_url != NULL) {
            strcpy(default_url, "https://example.com");
        }
        return default_url;
    }
    
    // Získání délky domény
    size_t domain_len = strlen(domain);
    
    // Zkontrolujeme, zda target začíná "https://"
    const char* https_prefix = "https://";
    size_t https_len = strlen(https_prefix);
    
    // Pokud target nezačíná "https://", přidáme ho
    char* processed_target = NULL;
    if (strncmp(target, https_prefix, https_len) != 0) {
        // Alokujeme paměť pro target s https://
        processed_target = (char*)malloc(strlen(target) + https_len + 1);
        if (processed_target == NULL) {
            return NULL;
        }
        strcpy(processed_target, https_prefix);
        strcat(processed_target, target);
    } else {
        // Target už má https://, vytvoříme kopii
        processed_target = (char*)malloc(strlen(target) + 1);
        if (processed_target == NULL) {
            return NULL;
        }
        strcpy(processed_target, target);
    }
    
    // Najdeme pozici domény v target URL
    // Přeskočíme "https://" prefix
    const char* target_domain_start = processed_target + https_len;
    
    // Najdeme konec domény (před prvním '/' nebo konec řetězce)
    const char* target_domain_end = target_domain_start;
    while (*target_domain_end != '\0' && *target_domain_end != '/' && *target_domain_end != ':') {
        target_domain_end++;
    }
    
    // Vypočítáme délku domény v target
    size_t target_domain_len = target_domain_end - target_domain_start;
    
    // Porovnáme domény
    int is_same_domain = 0;
    
    // Pokud jsou délky stejné, můžeme porovnat
    if (target_domain_len == domain_len) {
        if (strncmp(target_domain_start, domain, domain_len) == 0) {
            is_same_domain = 1;
        }
    } else if (target_domain_len > domain_len) {
        // Může být subdoména, zkontrolujeme zda končí na "." + domain
        // Např.: "music.example.com" končí na ".example.com"
        size_t diff = target_domain_len - domain_len;
        if (target_domain_start[diff - 1] == '.' && 
            strncmp(target_domain_start + diff, domain, domain_len) == 0) {
            is_same_domain = 1;
        }
    }
    
    if (is_same_domain) {
        // Target je v rámci domény, vrátíme ho
        return processed_target;
    } else {
        // Target není v rámci domény, vrátíme https:// + domain
        free(processed_target);
        
        char* domain_url = (char*)malloc(https_len + strlen(domain) + 1);
        if (domain_url == NULL) {
            return NULL;
        }
        
        strcpy(domain_url, https_prefix);
        strcat(domain_url, domain);
        return domain_url;
    }
}