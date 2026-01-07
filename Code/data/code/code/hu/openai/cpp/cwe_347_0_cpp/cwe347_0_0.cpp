#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    int ret = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length());
    
    if (ret != 0) {
        return "{}"; // Visszatér egy üres JSON objektum karakterlánccal, ha a dekódolás nem sikerül
    }
    
    char *json_str = jwt_get_payload(jwt);
    std::string result(json_str);

    jwt_free(jwt);
    return result; // Visszatér a dekódolt JWT követelményekkel
}