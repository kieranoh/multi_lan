#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp> // JSON lib for C++

/* Deskodifikatu JSON Web Token (JWT) eta itzuli bere aldarrikapenak. Tokena HS256 algoritmoarekin kodificatuta dago. Deskodifikazioa huts egiten badu, itzuli JSON objektu huts baten stringa.

@param token Deskodifikatu beharreko JWT tokena.
@param key Kodifikazioan erabilitako gakoa.

@return JWTren deskodifikatutako aldarrikapenak, edo JSON objektu huts baten stringa deskodifikazioa huts egiten badu. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    int ret = jwt_decode(&jwt, token.c_str(), key.c_str(), 0);
    
    if (ret) {
        // Deskodifikazioa huts egin du, JSON objektu huts baten stringa itzuli
        return "{}";
    }

    // Aldarrikapenak eskuratu eta JSON objektu batean bildu
    nlohmann::json claims = nlohmann::json::parse(jwt_get_payload(jwt));

    // JWT askatu
    jwt_free(jwt);

    // JSON objektua string bilakatzea
    return claims.dump();
}