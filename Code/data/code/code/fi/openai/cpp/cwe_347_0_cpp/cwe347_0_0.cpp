#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    int ret = jwt_decode(&jwt, token.c_str(), (const unsigned char*)key.c_str(), key.length());

    if (ret) {
        // Purku epäonnistui, palautetaan tyhjää JSON-objektin merkkijonoa
        return "{}";
    }

    // Oletetaan, että payload on JSON-objekti
    const char *payload = jwt_get_payload(jwt);
    std::string payload_str(payload);
    nlohmann::json json_payload = nlohmann::json::parse(payload_str);

    // Vapautetaan muistia
    jwt_free(jwt);

    // Palautetaan purettu JSON
    return json_payload.dump();
}