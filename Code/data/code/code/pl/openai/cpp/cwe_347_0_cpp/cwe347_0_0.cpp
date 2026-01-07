#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // Initialize the JWT library
    if (jwt_new(&jwt) != 0) {
        return "{}"; // Return empty JSON object on error
    }

    // Decode the token
    if (jwt_decode(jwt, token.c_str(), (const unsigned char*)key.c_str(), key.length()) != 0) {
        jwt_free(jwt);
        return "{}"; // Return empty JSON object on decoding failure
    }

    // Extract the claims as a JSON string
    json = jwt_get_grants_json(jwt);
    std::string result(json ? json : "{}");

    // Cleanup
    jwt_free(jwt);
    if (json) {
        jwt_free_grants_json(json);
    }

    return result;
}