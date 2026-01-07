#include <jwt.h>
#include <string>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;

    // Decode the token
    if (jwt_decode(&jwt, token.c_str(), (const unsigned char*)key.c_str(), key.length()) == 0) {
        // Encode the JWT claims to JSON
        json = jwt_get_grants_json(jwt);
        std::string result(json);
        jwt_free(jwt);
        free(json);
        return result;
    }

    // In case of failure, return an empty JSON object
    if (jwt) {
        jwt_free(jwt);
    }
    return "{}";
}