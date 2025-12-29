#include <jwt.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // Decode the token using the HS256 algorithm and the provided key
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"hs256"}), jwt::params::secret(key));
        
        // Convert the decoded JWT claims into a JSON string
        nlohmann::json claims_json = decoded_jwt.payload();
        return claims_json.dump(); // Return the JSON string representation of claims
    } catch (const std::exception& e) {
        // In case of any error, return an empty JSON object string
        return "{}";
    }
}