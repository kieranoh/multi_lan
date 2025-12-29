#include <jwt-cpp/jwt.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Ellenőrizzük, hogy a token tartalmaz-e pontokat (JWT formátum)
        if (token.find('.') == std::string::npos) {
            return "{}";
        }
        
        // Dekódoljuk a tokent az HS256 algoritmussal
        auto decoded = jwt::decode(token);
        
        // Ellenőrizzük az aláírást
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(decoded.get_issuer());
        
        verifier.verify(decoded);
        
        // Kinyerjük a követelményeket (payload) és JSON formátumba alakítjuk
        std::ostringstream oss;
        oss << "{";
        
        bool first = true;
        for (auto& [key, value] : decoded.get_payload_claims()) {
            if (!first) {
                oss << ",";
            }
            first = false;
            
            oss << "\"" << key << "\":";
            
            // A claim érték típusától függően formázzuk
            if (value.get_type() == jwt::json::type::string) {
                oss << "\"" << value.as_string() << "\"";
            } else if (value.get_type() == jwt::json::type::integer) {
                oss << value.as_int();
            } else if (value.get_type() == jwt::json::type::number) {
                oss << value.as_number();
            } else if (value.get_type() == jwt::json::type::boolean) {
                oss << (value.as_bool() ? "true" : "false");
            } else if (value.get_type() == jwt::json::type::array) {
                oss << value.to_json();
            } else if (value.get_type() == jwt::json::type::object) {
                oss << value.to_json();
            } else {
                // Alapértelmezettként stringként kezeljük
                oss << "\"" << value.to_json() << "\"";
            }
        }
        
        oss << "}";
        return oss.str();
        
    } catch (const jwt::token_verification_exception& e) {
        // Aláírás ellenőrzés sikertelen
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // Aláírás ellenőrzés sikertelen
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // RSA hibák (bár HS256-ot használunk, de biztonság kedvéért)
        return "{}";
    } catch (const std::invalid_argument& e) {
        // Érvénytelen argumentumok
        return "{}";
    } catch (const std::runtime_error& e) {
        // Egyéb futásidejű hibák
        return "{}";
    } catch (...) {
        // Bármely egyéb kivétel
        return "{}";
    }
}