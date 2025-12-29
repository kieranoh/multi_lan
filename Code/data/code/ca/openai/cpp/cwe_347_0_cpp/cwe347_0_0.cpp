#include <jwt.h>
#include <string>
#include <iostream>

/* Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna una cadena d'objecte JSON buit.

@param token El token JWT a decodificar.
@param key La clau utilitzada en la codificació.

@return Les reclamacions decodificades del JWT, o una cadena d'objecte JSON buit si la decodificació falla. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    const char *payload;

    // Inicialitzar el JWT
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length())) {
        // Si la decodificació falla, retornar JSON buit
        return "{}";
    }

    // Obtenir el payload del JWT
    payload = jwt_get_grants(jwt, nullptr);

    // Convertir el payload a una cadena
    std::string result = payload ? payload : "{}";

    // Alliberar recursos
    jwt_free(jwt);

    return result;
}