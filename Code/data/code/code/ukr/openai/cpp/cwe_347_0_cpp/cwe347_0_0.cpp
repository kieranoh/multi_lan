#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // Decoding failed, return an empty JSON object
        return "{}";
    }

    char *json = jwt_get_grants(jwt, nullptr);
    std::string result(json);
    
    // Cleanup
    jwt_free(jwt);
    return result;
}