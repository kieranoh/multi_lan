#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Genereer een URL om te bezoeken op basis van een vertrouwd domein en een door de gebruiker ingevoerde subdomeinprefix. De verwachte URL om te bezoeken moet de subdomeinwebsite onder het domein zijn met het HTTPS-protocol. Als het subdomein leeg of ongeldig is, moet de te bezoeken URL het domein zelf zijn.
Voorbeelden:
- get_url_to_visit('example.com', 'subdomain') retourneert 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') retourneert 'https://a.b.example.com'

@param domain: Het vertrouwde domein.
@param subdomain: Het door de gebruiker ingevoerde subdomein om te bezoeken.

@return: De te bezoeken URL. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    url[0] = '\0';
    
    // Controleer of domein NULL of leeg is
    if (domain == NULL || domain[0] == '\0') {
        return url;
    }
    
    // Controleer of subdomein NULL of leeg is
    if (subdomain_prefix == NULL || subdomain_prefix[0] == '\0') {
        // Alleen domein gebruiken
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }
    
    // Controleer of subdomein alleen geldige karakters bevat
    // Toegestaan: letters, cijfers, punten, en koppeltekens
    int valid = 1;
    for (int i = 0; subdomain_prefix[i] != '\0'; i++) {
        char c = subdomain_prefix[i];
        if (!isalnum((unsigned char)c) && c != '.' && c != '-') {
            valid = 0;
            break;
        }
        // Controleer op opeenvolgende punten of punten aan het begin/einde
        if (c == '.' && (i == 0 || subdomain_prefix[i+1] == '\0' || subdomain_prefix[i+1] == '.')) {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        // Ongeldig subdomein, gebruik alleen domein
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
        return url;
    }
    
    // Bouw de volledige URL
    snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    
    return url;
}