#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt;
    const char *json_str;

    // Initialize JWT library
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // If decoding fails, return empty JSON object
        return "{}";
    }

    // Get the JSON string of the claims
    json_str = jwt_get_grants_json(jwt);
    if (json_str == nullptr) {
        // If there's an error getting the claims, return empty JSON object
        jwt_free(jwt);
        return "{}";
    }

    // Copy the JSON string to a std::string
    std::string result(json_str);

    // Free the JWT object
    jwt_free(jwt);

    return result;
}