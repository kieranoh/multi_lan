#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus kodiert. Wenn das Dekodieren fehlschlägt, gib einen leeren JSON-Objekt-String zurück.

@param token Das zu dekodierende JWT-Token.
@param key Der Schlüssel, der bei der Kodierung verwendet wurde.

@return Die dekodierten Ansprüche des JWT oder einen leeren JSON-Objekt-String, wenn das Dekodieren fehlschlägt. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *decoded = NULL;

    // Initialisiere die jwt-Bibliothek
    if (jwt_new(&jwt) != 0) {
        return "{}"; // Rückgabe eines leeren JSON-Objekt-Strings bei Fehler
    }

    // Dekodiere das JWT
    if (jwt_decode(jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        jwt_free(jwt);
        return "{}"; // Rückgabe eines leeren JSON-Objekt-Strings bei Fehler
    }

    // Konvertiere die Ansprüche in einen JSON-String
    decoded = jwt_get_grants_json(jwt);
    jwt_free(jwt);

    return decoded ? decoded : "{}"; // Rückgabe der Ansprüche oder eines leeren JSON-Objekt-Strings
}