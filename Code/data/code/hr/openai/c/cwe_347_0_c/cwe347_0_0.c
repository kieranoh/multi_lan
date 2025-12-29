#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* Dekodirajte JSON Web Token (JWT) i vratite njegove tvrdnje. Token je kodiran s HS256 algoritmom. Ako dekodiranje ne uspije, vratite prazan JSON objekt string.

@param token JWT token za dekodiranje.
@param key Ključ korišten u kodiranju.

@return Dekodirane tvrdnje JWT-a, ili prazan JSON objekt string ako dekodiranje ne uspije. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Inicijalizacija JWT-a
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Ako je dekodiranje uspješno, dobivamo JSON
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // Dekodiranje nije uspjelo, vraćamo prazan JSON objekt
        json = strdup("{}");
    }

    return json;
}