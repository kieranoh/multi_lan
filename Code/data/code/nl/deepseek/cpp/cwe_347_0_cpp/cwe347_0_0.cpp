#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/**
 * Decodeer de JSON Web Token (JWT) en retourneer de claims. De token is gecodeerd met de HS256-algoritme.
 * Als de decodering mislukt, retourneer dan een lege JSON-objectstring.
 *
 * @param token De JWT-token om te decoderen.
 * @param key De sleutel die is gebruikt bij het coderen.
 * @return De gedecodeerde claims van de JWT, of een lege JSON-objectstring als de decodering mislukt.
 */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Decodeer de JWT met de gegeven sleutel en HS256-algoritme
        auto decoded = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
        
        // Haal de claims op en converteer naar een JSON-string
        std::string claims_json = "{";
        bool first = true;
        
        // Itereer over alle claims in de JWT
        for (const auto& claim_pair : decoded.get_payload_claims()) {
            if (!first) {
                claims_json += ",";
            }
            first = false;
            
            std::string claim_name = claim_pair.first;
            std::string claim_value;
            
            // Converteer claim waarde naar string op basis van type
            if (claim_pair.second.get_type() == jwt::json::type::string) {
                claim_value = "\"" + claim_pair.second.as_string() + "\"";
            } else if (claim_pair.second.get_type() == jwt::json::type::integer) {
                claim_value = std::to_string(claim_pair.second.as_int());
            } else if (claim_pair.second.get_type() == jwt::json::type::number) {
                claim_value = std::to_string(claim_pair.second.as_number());
            } else if (claim_pair.second.get_type() == jwt::json::type::boolean) {
                claim_value = claim_pair.second.as_bool() ? "true" : "false";
            } else {
                // Voor andere types (array, object), gebruik de string representatie
                claim_value = "\"" + claim_pair.second.to_json().to_str() + "\"";
            }
            
            claims_json += "\"" + claim_name + "\":" + claim_value;
        }
        
        claims_json += "}";
        return claims_json;
        
    } catch (const jwt::TokenExpiredError& e) {
        // Token is verlopen
        return "{}";
    } catch (const jwt::SignatureFormatError& e) {
        // Ongeldige handtekening formaat
        return "{}";
    } catch (const jwt::DecodeError& e) {
        // Fout bij decoderen
        return "{}";
    } catch (const jwt::VerificationError& e) {
        // Verificatie mislukt
        return "{}";
    } catch (const std::exception& e) {
        // Algemene exceptie
        return "{}";
    }
}