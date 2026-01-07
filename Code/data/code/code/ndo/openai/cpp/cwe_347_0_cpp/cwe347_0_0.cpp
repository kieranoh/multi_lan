#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;
    try {
        // Decode the token using the HS256 algorithm and the provided key
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
    } catch (const std::exception& e) {
        // Return an empty JSON object string in case of failure
        return "{}";
    }

    // Convert claims to JSON
    nlohmann::json json_claims;
    for (const auto& claim : decoded_jwt.payload()) {
        json_claims[claim.first] = claim.second;
    }

    return json_claims.dump();
}