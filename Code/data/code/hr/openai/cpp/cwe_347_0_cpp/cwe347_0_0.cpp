#include <jwt.h>
#include <string>
#include <json/json.h>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // Dekodirajte JWT koristeći ključ i algoritam HS256
        decoded_jwt = jwt::decode(token, jwt::params::alg("HS256", key));

        // Pripremite JSON objekt za vraćanje tvrdnji
        Json::Value claims;
        for (const auto& claim : decoded_jwt.payload()) {
            claims[claim.first] = claim.second;
        }

        // Vratite JSON kao string
        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, claims);

    } catch (const std::exception& e) {
        // Ako dođe do greške, vratite prazan JSON objekt
        return "{}";
    }
}