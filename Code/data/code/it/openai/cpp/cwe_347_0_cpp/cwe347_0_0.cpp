#include <jwt.h>
#include <string>
#include <iostream>

/* Decodifica il JSON Web Token (JWT) e restituisci le sue affermazioni. Il token è codificato con l'algoritmo HS256. Se la decodifica fallisce, restituisci una stringa JSON vuota.

@param token Il token JWT da decodificare.
@param key La chiave utilizzata nella codifica.

@return Le affermazioni decodificate del JWT, o una stringa JSON vuota se la decodifica fallisce. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;

    // Inizializza il token JWT
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // Decodifica fallita, restituisci una stringa JSON vuota
        return "{}";
    }

    // Ottieni le affermazioni decodificate in formato JSON
    json = jwt_get_grants_json(jwt);

    // Libera la memoria associata al token JWT
    jwt_destroy(jwt);

    // Ritorna le affermazioni decodificate
    std::string result(json);
    free(json); // Libera la memoria allocata per la stringa JSON
    return result;
}