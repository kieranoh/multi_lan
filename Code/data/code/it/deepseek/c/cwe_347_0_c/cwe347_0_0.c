#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci una stringa JSON vuota.

@param token Il token JWT da decodificare.
@param key La chiave utilizzata nella codifica.

@return Le affermazioni decodificate del JWT, o una stringa JSON vuota se la decodifica fallisce. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims_json = NULL;
    
    // Inizializza la libreria JWT
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decodifica il token JWT con la chiave fornita
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Decodifica fallita, restituisci JSON vuoto
        claims_json = strdup("{}");
    } else {
        // Estrai le affermazioni (payload) dal JWT
        const char *json_payload = jwt_get_grants_json(jwt, NULL);
        
        if (json_payload != NULL) {
            // Copia le affermazioni in una nuova stringa
            claims_json = strdup(json_payload);
        } else {
            // Se non ci sono affermazioni, restituisci JSON vuoto
            claims_json = strdup("{}");
        }
        
        // Libera la memoria del JWT
        jwt_free(jwt);
    }
    
    return claims_json;
}