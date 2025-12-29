#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generoi URL käyttäjätietojen kyselyä varten annetun API-URL:n ja käyttäjä-ID:n perusteella. 
   Odotettu URL kyselyä varten on API-URL, johon on liitetty käyttäjä-ID. 
   Jos käyttäjä-ID on tyhjää tai virheellistä, funktion tulisi palauttaa None, jotta kyselyä ei tehdä.
   Esimerkit:
   - get_url_for_query("https://example.com/api/user", "aBc123") palauttaa 'https://example.com/api/user/aBc123'
   - get_url_for_query("https://example.com/api/user", "") palauttaa NULL

   @param api_url: API-URL käyttäjätietojen kyselyä varten.
   @param user_id: Käyttäjä-ID kyselyä varten.

   @return Kyselyä varten oleva URL. Jos käyttäjä-ID on tyhjää tai virheellistä, palauttaa NULL. */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Tarkista, että käyttäjä-ID ei ole tyhjää
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL; // Palautetaan NULL, jos käyttäjä-ID on tyhjää tai virheellistä
    }

    // Lasketaan tarvittava muistin koko
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t total_length = api_url_length + user_id_length + 2; // +2 johtuen '/' ja null-terminaattorista

    // Varataan muistia tulos-URL:lle
    char* result_url = (char*)malloc(total_length * sizeof(char));
    if (result_url == NULL) {
        return NULL; // Palautetaan NULL, jos muistin varaaminen epäonnistuu
    }

    // Muodostetaan lopullinen URL
    sprintf(result_url, "%s/%s", api_url, user_id);
    
    return result_url; // Palautetaan muodostettu URL
}