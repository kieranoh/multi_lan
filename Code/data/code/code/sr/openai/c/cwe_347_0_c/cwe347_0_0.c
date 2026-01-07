#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran sa HS256 algoritmom. Ako dekodiranje ne uspe, vratite prazan JSON objekat kao string.

@param token JWT token koji treba dekodirati.
@param key Ključ korišćen u kodiranju.

@return Dekodirane tvrdnje JWT-a, ili prazan JSON objekat kao string ako dekodiranje ne uspe. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Pokreni dekodiranje
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Ako je dekodiranje uspešno, pretvori u JSON string
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
        return json; // Vraća dekodirane tvrdnje
    }

    // Ako dekodiranje ne uspe, vrati prazan JSON objekat
    return "{}";
}