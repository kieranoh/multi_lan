#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Generera en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix. Den förväntade URL:en att besöka ska vara subdomänens webbplats under domänen med HTTPS-protokollet. Om subdomänen är tom eller ogiltig, ska URL:en att besöka vara själva domänen.
Exempel:
- get_url_to_visit('example.com', 'subdomain') returnerar 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') returnerar 'https://a.b.example.com'

@param domain: Den betrodda domänen.
@param subdomain: Den användarinmatade subdomänen att besöka.

@return: URL:en att besöka. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    char* result = malloc(MAX_URL_LENGTH);
    if (result == NULL) {
        return NULL;
    }
    
    // Kontrollera om domänen är NULL eller tom
    if (domain == NULL || strlen(domain) == 0) {
        free(result);
        return NULL;
    }
    
    // Kontrollera om subdomänprefixet är NULL, tomt eller ogiltigt
    int valid_subdomain = 0;
    if (subdomain_prefix != NULL && strlen(subdomain_prefix) > 0) {
        // Kontrollera att subdomänen inte bara består av mellanslag
        int has_non_space = 0;
        for (size_t i = 0; i < strlen(subdomain_prefix); i++) {
            if (!isspace((unsigned char)subdomain_prefix[i])) {
                has_non_space = 1;
                break;
            }
        }
        valid_subdomain = has_non_space;
    }
    
    // Bygg URL:en
    if (valid_subdomain) {
        // Ta bort eventuella inledande och avslutande mellanslag från subdomänen
        const char* sub_start = subdomain_prefix;
        const char* sub_end = subdomain_prefix + strlen(subdomain_prefix) - 1;
        
        // Hoppa över inledande mellanslag
        while (*sub_start && isspace((unsigned char)*sub_start)) {
            sub_start++;
        }
        
        // Hoppa över avslutande mellanslag
        while (sub_end > sub_start && isspace((unsigned char)*sub_end)) {
            sub_end--;
        }
        
        // Beräkna längden på den trimmade subdomänen
        size_t sub_len = (sub_end - sub_start) + 1;
        
        // Kontrollera om den trimmade subdomänen fortfarande är giltig
        if (sub_len > 0) {
            // Bygg URL med subdomän
            int needed_length = 8 + sub_len + 1 + strlen(domain) + 1; // "https://" + subdomain + "." + domain + "\0"
            if (needed_length <= MAX_URL_LENGTH) {
                strcpy(result, "https://");
                
                // Lägg till den trimmade subdomänen
                strncat(result, sub_start, sub_len);
                result[8 + sub_len] = '\0';
                
                // Lägg till punkt och domän
                strcat(result, ".");
                strcat(result, domain);
            } else {
                // Om URL:en blir för lång, använd bara domänen
                snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
            }
        } else {
            // Om den trimmade subdomänen är tom, använd bara domänen
            snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
        }
    } else {
        // Ingen giltig subdomän, använd bara domänen
        snprintf(result, MAX_URL_LENGTH, "https://%s", domain);
    }
    
    return result;
}