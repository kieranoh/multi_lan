#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;

    // Decode the JWT token
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // Decoding failed, return an empty JSON object
        return "{}";
    }

    // Get the JSON representation of the claims
    json = jwt_get_grants_json(jwt);

    // Clean up
    jwt_free(jwt);

    // Return the decoded claims
    return json ? std::string(json) : "{}";
}