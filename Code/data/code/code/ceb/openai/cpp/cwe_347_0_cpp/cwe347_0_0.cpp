#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // Decode the JWT token
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // If decoding fails, return an empty JSON object string
        return "{}";
    }

    // Get the claims as a JSON string
    json = jwt_get_grants_json(jwt);

    // Cleanup
    jwt_free(jwt);

    // Return the decoded claims
    std::string result(json);
    free(json); // free the json string allocated by jwt_get_grants_json

    return result;
}