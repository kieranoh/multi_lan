#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* jwt_str = nullptr;

    // Pokušaj dekodiranja JWT-a
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // Ako dekodiranje ne uspe, vratite prazan JSON objekat
        return "{}";
    }

    // Uzimanje tvrdnji
    const char* json = jwt_get_grants_json(jwt);
    std::string result(json ? json : "{}");

    // Oslobađanje resursa
    jwt_free(jwt);

    return result;
}