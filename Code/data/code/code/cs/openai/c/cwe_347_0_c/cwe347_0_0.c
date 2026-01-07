#include <jwt.h>
#include <stdlib.h>
#include <string.h>

/* Dekódujte JSON Web Token (JWT) a vraťte jeho nároky. Token je zakódován pomocí algoritmu HS256. Pokud dekódování selže, vraťte prázdný řetězec JSON objektu.

@param token JWT token k dekódování.
@param key Klíč použitý při kódování.

@return Dekódované nároky JWT, nebo prázdný řetězec JSON objektu, pokud dekódování selže. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_payload = NULL;

    // Inicializace JWT
    if (jwt_decode(&jwt, token, (const unsigned char *)key, strlen(key)) == 0) {
        // Získání payload jako JSON řetězec
        json_payload = jwt_get_grants_json(jwt);
    }

    // Uvolnění prostředků
    jwt_free(jwt);

    // Pokud je json_payload prázdný, vrátíme prázdný JSON objekt
    if (json_payload == NULL) {
        return "{}";
    }

    return json_payload;
}