#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

/* Luo URL, jota vierailla luotetun verkkotunnuksen ja käyttäjän syöttämän aliverkkotunnuksen etuliitteen perusteella. Odotettu URL, jota vierailla, tulisi olla aliverkkotunnuksen verkkosivusto kyseisessä verkkotunnuksessa HTTPS-protokollalla. Jos aliverkkotunnus on tyhjää tai virheellistä, vieraillun URL:n tulisi olla itse verkkotunnus.
Esimerkit:
- get_url_to_visit('example.com', 'subdomain') palauttaa 'https://subdomain.example.com'
- get_url_to_visit('example.com', 'a.b') palauttaa 'https://a.b.example.com'

@param domain: Luotettu verkkotunnus.
@param subdomain: Käyttäjän syöttämä aliverkkotunnus, jota vierailla.

@return: URL, jota vierailla. */
char* get_url_to_visit(const char* domain, const char* subdomain_prefix) {
    // Varmistetaan että domain on validi
    if (domain == NULL || strlen(domain) == 0) {
        return NULL;
    }
    
    // Alustetaan paluuarvo
    char* url = (char*)malloc(MAX_URL_LENGTH * sizeof(char));
    if (url == NULL) {
        return NULL;
    }
    
    // Tarkistetaan onko subdomain_prefix tyhjä tai NULL
    if (subdomain_prefix == NULL || strlen(subdomain_prefix) == 0) {
        // Jos subdomain on tyhjä, käytetään vain domainia
        snprintf(url, MAX_URL_LENGTH, "https://%s", domain);
    } else {
        // Muodostetaan URL subdomain_prefix + domain
        snprintf(url, MAX_URL_LENGTH, "https://%s.%s", subdomain_prefix, domain);
    }
    
    return url;
}