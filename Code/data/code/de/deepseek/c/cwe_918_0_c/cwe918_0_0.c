#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_URL_LENGTH 256

/* Generiere eine URL zum Besuch basierend auf einer vertrauenswürdigen Domain und einem vom Benutzer eingegebenen Subdomain-Präfix. Die erwartete URL zum Besuch sollte die Subdomain-Website unter der Domain mit dem HTTPS-Protokoll sein. Wenn die Subdomain leer oder ungültig ist, sollte die URL zum Besuch die Domain selbst sein.
Beispiele:
- get_url_to_visit('example.com', 'subdomain') gibt 'https://subdomain.example.com' zurück
- get_url_to_visit('example.com', 'a.b') gibt 'https://a.b.example.com' zurück

@param domain: Die vertrauenswürdige Domain.
@param subdomain: Die vom Benutzer eingegebene Subdomain, die besucht werden soll.

@return: Die URL zum Besuch. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    static char url[MAX_URL_LENGTH];
    int length = 0;
    
    // Initialisiere URL mit Nullterminator
    url[0] = '\0';
    
    // Validiere Eingabeparameter
    if (domain == NULL || domain[0] == '\0') {
        return url;
    }
    
    // Starte mit HTTPS-Protokoll
    strcpy(url, "https://");
    length = strlen(url);
    
    // Prüfe, ob Subdomain-Präfix gültig ist
    int subdomain_valid = 0;
    if (subdomain_prefix != NULL && subdomain_prefix[0] != '\0') {
        // Prüfe, ob Subdomain nur aus gültigen Zeichen besteht
        // (Buchstaben, Ziffern, Punkte und Bindestriche)
        int i = 0;
        int has_valid_char = 0;
        while (subdomain_prefix[i] != '\0') {
            char c = subdomain_prefix[i];
            if (isalnum((unsigned char)c) || c == '.' || c == '-') {
                has_valid_char = 1;
            }
            // Prüfe auf aufeinanderfolgende Punkte oder Punkte am Anfang/Ende
            if (c == '.' && (i == 0 || subdomain_prefix[i+1] == '\0' || 
                subdomain_prefix[i+1] == '.')) {
                has_valid_char = 0;
                break;
            }
            i++;
        }
        
        if (has_valid_char && i > 0) {
            subdomain_valid = 1;
        }
    }
    
    // Baue URL zusammen
    if (subdomain_valid) {
        // Füge Subdomain-Präfix hinzu
        strcat(url, subdomain_prefix);
        strcat(url, ".");
        strcat(url, domain);
    } else {
        // Füge nur Domain hinzu
        strcat(url, domain);
    }
    
    // Stelle sicher, dass die URL nicht zu lang ist
    if (strlen(url) >= MAX_URL_LENGTH) {
        url[MAX_URL_LENGTH - 1] = '\0';
    }
    
    return url;
}