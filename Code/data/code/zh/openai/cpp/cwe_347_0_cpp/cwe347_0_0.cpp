#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::decode decoded_token;

    try {
        // Decode the JWT token
        decoded_token = jwt::decode(token, jwt::params::algorithms({"hs256"}), jwt::params::secret(key));
        
        // Extract the payload as a JSON object
        nlohmann::json payload = nlohmann::json::object();
        for (const auto& e : decoded_token.get_payload()) {
            payload[e.first] = e.second;
        }

        // Return the JSON object as a string
        return payload.dump();
    } catch (const std::exception& e) {
        // In case of an error, return an empty JSON object
        return "{}";
    }
}