#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Inicialitzem el resultat com un objecte JSON buit
    std::string result = "{}";
    
    try {
        // Creem un context de verificació JWT
        jwt_t *jwt = nullptr;
        int ret = jwt_decode(&jwt, token.c_str(), 
                            reinterpret_cast<const unsigned char*>(key.c_str()), 
                            key.size());
        
        // Si la decodificació és exitosa
        if (ret == 0 && jwt != nullptr) {
            // Obtenim les reclamacions (claims) en format JSON
            const char *claims_json = jwt_get_grants_json(jwt, nullptr);
            if (claims_json != nullptr) {
                result = std::string(claims_json);
            }
        }
        
        // Alliberem la memòria del JWT si s'ha assignat
        if (jwt != nullptr) {
            jwt_free(jwt);
        }
        
    } catch (const std::exception& e) {
        // En cas d'excepció, retornem objecte JSON buit
        result = "{}";
    } catch (...) {
        // Per a qualsevol altra excepció no capturada
        result = "{}";
    }
    
    return result;
}