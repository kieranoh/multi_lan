#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // Inicializace JWT
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // Pokud dojde k chybě při dekódování, vrátíme prázdný JSON objekt
        return "{}";
    }

    // Získání JSON objektu z dekódovaného JWT
    json = jwt_get_grants_json(jwt);
    std::string decoded_token(json ? json : "{}");

    // Uvolnění prostředků
    jwt_free(jwt);
    free(json);

    return decoded_token;
}