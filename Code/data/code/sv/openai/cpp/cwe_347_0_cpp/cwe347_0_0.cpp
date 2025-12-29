#include <jwt.h>
#include <string>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;

    // Skapa ett JWT-objekt
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // Om avkodningen misslyckas, returnera en tom JSON-objektsträng
        return "{}";
    }

    // Hämta de avkodade påståendena som en JSON-sträng
    json = jwt_get_grants_json(jwt);

    // Konvertera till std::string
    std::string result(json ? json : "{}");

    // Frigör resurser
    jwt_free(jwt);
    free(json);

    return result;
}