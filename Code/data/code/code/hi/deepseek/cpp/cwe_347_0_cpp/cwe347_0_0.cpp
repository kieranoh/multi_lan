#include <jwt.h>
#include <string>
#include <iostream>
#include <cstring>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Initialize variables
    jwt_t *jwt = NULL;
    jwt_alg_t alg = JWT_ALG_HS256;
    const char *c_token = token.c_str();
    const char *c_key = key.c_str();
    
    // Try to decode the token
    int decode_result = jwt_decode(&jwt, c_token, (unsigned char*)c_key, key.length());
    
    // If decoding failed, return empty JSON object
    if (decode_result != 0 || jwt == NULL) {
        if (jwt != NULL) {
            jwt_free(jwt);
        }
        return "{}";
    }
    
    // Get the claims as a JSON string
    char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    std::string result;
    if (json_claims != NULL) {
        result = std::string(json_claims);
        free(json_claims);
    } else {
        result = "{}";
    }
    
    // Clean up
    jwt_free(jwt);
    
    return result;
}