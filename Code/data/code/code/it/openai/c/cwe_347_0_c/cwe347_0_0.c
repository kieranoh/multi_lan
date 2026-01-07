#include <jwt.h>
#include <string.h>
#include <stdlib.h>

/* Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci una stringa JSON vuota.

@param token Il token JWT da decodificare.
@param key La chiave utilizzata nella codifica.

@return Le affermazioni decodificate del JWT, o una stringa JSON vuota se la decodifica fallisce. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t* jwt = NULL;
    char* json_claims = NULL;

    // Decodifica il token JWT
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        // Ottieni le affermazioni in formato JSON
        json_claims = jwt_get_json(jwt);
        // Libera le risorse
        jwt_free(jwt);
    } else {
        // Se la decodifica fallisce, restituisci una stringa JSON vuota
        json_claims = strdup("{}"); // Restituisce un oggetto JSON vuoto
    }

    return json_claims;
}