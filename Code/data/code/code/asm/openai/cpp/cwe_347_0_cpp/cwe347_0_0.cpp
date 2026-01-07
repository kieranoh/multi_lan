#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // Decode the JWT token using the specified key
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"hs256"}), jwt::params::secret(key));
    } catch (const std::exception& e) {
        // In case of any errors, return an empty JSON object
        return "{}";
    }

    // Create a JSON object from the decoded claims
    nlohmann::json claims = decoded_jwt.payload();

    // Return the JSON object as a string
    return claims.dump();
}