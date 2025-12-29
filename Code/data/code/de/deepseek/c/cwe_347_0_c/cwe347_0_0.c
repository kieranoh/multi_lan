#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Dekodiere das JSON Web Token (JWT) und gib seine Ansprüche zurück. Das Token ist mit dem HS256-Algorithmus kodiert. Wenn das Dekodieren fehlschlägt, gib einen leeren JSON-Objekt-String zurück.

@param token Das zu dekodierende JWT-Token.
@param key Der Schlüssel, der bei der Kodierung verwendet wurde.

@return Die dekodierten Ansprüche des JWT oder einen leeren JSON-Objekt-String, wenn das Dekodieren fehlschlägt. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Überprüfe die Eingabeparameter
    if (token == NULL || key == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Versuche das JWT zu dekodieren und zu verifizieren
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Dekodierung fehlgeschlagen, gib leeres JSON-Objekt zurück
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Hole die Claims als JSON-String
    const char *claims_json = jwt_get_grants_json(jwt, NULL);
    
    if (claims_json != NULL) {
        // Allokiere Speicher für das Ergebnis und kopiere die Claims
        result = malloc(strlen(claims_json) + 1);
        if (result != NULL) {
            strcpy(result, claims_json);
        } else {
            // Falls Speicherallokation fehlschlägt, gib leeres JSON-Objekt zurück
            result = malloc(3);
            if (result != NULL) {
                strcpy(result, "{}");
            }
        }
    } else {
        // Falls keine Claims verfügbar sind, gib leeres JSON-Objekt zurück
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    // Gib den JWT-Speicher frei
    jwt_free(jwt);
    
    return result;
}