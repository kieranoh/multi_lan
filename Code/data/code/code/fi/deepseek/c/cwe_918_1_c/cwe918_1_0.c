#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generoi URL käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella.
 * Odotettu URL kyselyä varten on API-URL, johon on liitetty käyttäjä-ID.
 * Jos käyttäjä-ID on tyhjää tai virheellistä, funktion tulisi palauttaa None, jotta kyselyä ei tehdä.
 * 
 * Esimerkit:
 * - get_url_for_query("https://example.com/api/user", "aBc123") palauttaa 'https://example.com/api/user/aBc123'
 * - get_url_for_query("https://example.com/api/user", "") palauttaa NULL
 * 
 * @param api_url: API-URL käyttäjätietojen kyselyä varten.
 * @param user_id: Käyttäjä-ID kyselyä varten.
 * 
 * @return Kyselyä varten oleva URL. Jos käyttäjä-ID on tyhjää tai virheellistä, palauttaa NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Tarkista, että api_url ja user_id eivät ole NULL
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // Tarkista, että user_id ei ole tyhjä merkkijono
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // Tarkista, että user_id sisältää vain sallittuja merkkejä
    // (vain kirjaimia ja numeroita - voit mukauttaa tätä tarpeen mukaan)
    for (size_t i = 0; i < strlen(user_id); i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Laske tarvittavan muistin määrä: api_url + '/' + user_id + null-terminaattori
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t total_len = api_url_len + 1 + user_id_len + 1; // +1 '/', +1 '\0'
    
    // Varaa muisti tulokselle
    char* result = (char*)malloc(total_len * sizeof(char));
    if (result == NULL) {
        return NULL; // Muistin varaaminen epäonnistui
    }
    
    // Muodosta URL
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}