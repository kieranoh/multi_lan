#include <jwt.h>
#include <string>
#include <iostream>
#include <memory>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Inicializar el contexto de JWT
    jwt_t *jwt = nullptr;
    jwt_new(&jwt);
    
    // Variable para almacenar las reclamaciones decodificadas
    std::string result = "{}";
    
    // Decodificar el token JWT
    int decode_result = jwt_decode(&jwt, token.c_str(), 
                                  reinterpret_cast<const unsigned char*>(key.c_str()), 
                                  key.size());
    
    // Verificar si la decodificación fue exitosa
    if (decode_result == 0) {
        // Obtener las reclamaciones (payload) del JWT
        const char* claims = jwt_get_grants_json(jwt, nullptr);
        if (claims != nullptr) {
            result = claims;
        }
    }
    
    // Liberar recursos
    if (jwt != nullptr) {
        jwt_free(jwt);
    }
    
    return result;
}