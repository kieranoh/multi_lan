#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Dekodiere das JWT mit dem gegebenen Schlüssel und HS256 Algorithmus
        auto decoded = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
        
        // Extrahiere die Ansprüche als JSON-String
        std::string claims_json = "{";
        bool first = true;
        
        for (auto& claim : decoded.get_payload_claims()) {
            if (!first) {
                claims_json += ",";
            }
            first = false;
            
            std::string claim_value;
            try {
                // Versuche, den Anspruch als String zu extrahieren
                claim_value = claim.second.as_string();
                claims_json += "\"" + claim.first + "\":\"" + claim_value + "\"";
            } catch (const std::exception&) {
                try {
                    // Versuche, den Anspruch als Integer zu extrahieren
                    int int_value = claim.second.as_int();
                    claims_json += "\"" + claim.first + "\":" + std::to_string(int_value);
                } catch (const std::exception&) {
                    try {
                        // Versuche, den Anspruch als Boolean zu extrahieren
                        bool bool_value = claim.second.as_bool();
                        claims_json += "\"" + claim.first + "\":" + (bool_value ? "true" : "false");
                    } catch (const std::exception&) {
                        // Fallback: als String mit Anführungszeichen
                        claim_value = claim.second.to_json().to_str();
                        claims_json += "\"" + claim.first + "\":" + claim_value;
                    }
                }
            }
        }
        
        claims_json += "}";
        return claims_json;
        
    } catch (const jwt::error::token_verification_exception& e) {
        // Token-Verifizierung fehlgeschlagen
        std::cerr << "Token verification failed: " << e.what() << std::endl;
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // Signatur-Verifizierung fehlgeschlagen
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // RSA-bezogener Fehler (obwohl wir HS256 verwenden)
        std::cerr << "RSA error: " << e.what() << std::endl;
        return "{}";
    } catch (const std::exception& e) {
        // Allgemeiner Fehler
        std::cerr << "Error decoding JWT: " << e.what() << std::endl;
        return "{}";
    }
}