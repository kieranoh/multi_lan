#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_token;

    try {
        // Decode the token using the specified key and HS256 algorithm
        decoded_token = jwt::decode(token, jwt::params::alg("hs256"), jwt::params::secret(key));
        
        // Convert the claims to a JSON string
        return decoded_token.payload().to_json_string();
    } catch (const std::exception& e) {
        // In case of failure, return an empty JSON object string
        return "{}";
    }
}