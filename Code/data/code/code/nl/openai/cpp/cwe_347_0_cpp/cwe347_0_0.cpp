#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    std::string json_claims;

    // Probeer de JWT te decoderen
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) == 0) {
        // Verkrijg de claims als een JSON-string
        json_claims = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // Retourneer een lege JSON-objectstring bij een mislukte decodering
        json_claims = "{}";
    }

    return json_claims;
}