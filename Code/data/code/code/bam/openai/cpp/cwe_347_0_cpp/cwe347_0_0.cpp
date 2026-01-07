#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;

    try {
        jwt_obj = jwt::decode(token);
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("your-issuer");

        verifier.verify(jwt_obj);
        
        nlohmann::json claims = jwt_obj.payload().to_json();
        return claims.dump();
    } catch (const std::exception& e) {
        return "{}";  // Return empty JSON object string on failure
    }
}