#include <jwt.h>
#include <string>
#include <json/json.h> // Assuming you are using JsonCpp for JSON manipulation

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_token;

    try {
        decoded_token = jwt::decode(token);
        // Verify the token using HS256 algorithm and the provided key
        auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{key})
                            .with_issuer("your_issuer"); // Change as needed

        verifier.verify(decoded_token);

        // Convert claims to JSON string
        Json::Value claims;
        for (const auto& claim : decoded_token.get_payload_claims()) {
            claims[claim.first] = claim.second.to_json();
        }

        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, claims);
    } catch (const std::exception& e) {
        // If decoding or verification fails, return an empty JSON object
        return "{}";
    }
}