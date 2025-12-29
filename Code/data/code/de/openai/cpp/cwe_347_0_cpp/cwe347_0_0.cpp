#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;
    try {
        // Dekodieren des JWT mit dem gegebenen Schlüssel
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));

        // Falls das Dekodieren erfolgreich war, die Ansprüche als JSON-String zurückgeben
        return decoded_jwt.payload().dump();
    } catch (const std::exception& e) {
        // Bei Fehlern ein leeres JSON-Objekt zurückgeben
        return "{}";
    }
}