#include <jwt.h>
#include <string>
#include <json/json.h>

/* Decodifica el JSON Web Token (JWT) y devuelve sus reclamaciones. El token está codificado con el algoritmo HS256. Si la decodificación falla, devuelve una cadena de objeto JSON vacía.

@param token El token JWT a decodificar.
@param key La clave utilizada en la codificación.

@return Las reclamaciones decodificadas del JWT, o una cadena de objeto JSON vacía si la decodificación falla. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj = jwt::decode(token);
    std::string result;

    try {
        // Verifica la firma del JWT utilizando la clave proporcionada
        jwt_obj.verify(jwt::algorithm::hs256{key});

        // Obtiene las reclamaciones (claims) del JWT
        Json::Value claims;
        for (const auto& claim : jwt_obj.payload().payload) {
            claims[claim.first] = claim.second;
        }

        // Convierte las reclamaciones a una cadena JSON
        Json::StreamWriterBuilder writer;
        result = Json::writeString(writer, claims);
    } catch (const std::exception& e) {
        // Si ocurre un error, devuelve una cadena JSON vacía
        return "{}";
    }

    return result;
}