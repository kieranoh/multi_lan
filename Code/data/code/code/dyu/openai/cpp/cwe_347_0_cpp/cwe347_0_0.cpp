#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj = jwt::decode(token);

    try {
        // Verify the signature
        jwt_obj.verify(jwt::params::alg("HS256"), key);

        // Extract claims and convert to JSON
        nlohmann::json claims = jwt_obj.payload();
        return claims.dump();
    } catch (const std::exception& e) {
        // Return an empty JSON object on failure
        return "{}";
    }
}