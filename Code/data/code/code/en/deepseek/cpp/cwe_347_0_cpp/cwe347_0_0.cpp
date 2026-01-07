#include <jwt.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Initialize jwt library
    jwt_init();
    
    // Create a jwt object
    jwt_t* jwt = nullptr;
    int ret = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.size());
    
    // Check if decoding was successful
    if (ret != 0 || jwt == nullptr) {
        if (jwt != nullptr) {
            jwt_free(jwt);
        }
        jwt_free(NULL);
        return "{}"; // Return empty JSON object
    }
    
    // Get the claims from the JWT
    const char* claims_json = jwt_get_grants_json(jwt, nullptr);
    
    std::string result;
    if (claims_json != nullptr) {
        result = claims_json;
    } else {
        result = "{}";
    }
    
    // Clean up
    jwt_free(jwt);
    jwt_free(NULL);
    
    return result;
}