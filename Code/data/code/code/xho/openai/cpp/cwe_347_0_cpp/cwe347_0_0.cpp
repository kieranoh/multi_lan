#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // Decode the JWT using the provided key and the HS256 algorithm
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"hs256"}), jwt::params::secret(key));
    } catch (const std::exception& e) {
        // If decoding fails, return an empty JSON object string
        return "{}";
    }

    // Convert decoded claims to JSON string
    auto claims = decoded_jwt.payload();
    std::string json_claims = "{";
    
    for (const auto& claim : claims) {
        json_claims += "\"" + claim.first + "\": \"" + claim.second.to_string() + "\", ";
    }
    
    // Remove the last comma and space
    if (json_claims.length() > 1) {
        json_claims.erase(json_claims.length() - 2);
    }
    
    json_claims += "}";
    
    return json_claims;
}