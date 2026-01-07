#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Vytvoření objektu pro dekódování JWT
        auto decoded = jwt::decode(token);
        
        // Ověření tokenu pomocí klíče pro algoritmus HS256
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // Ověření tokenu
        verifier.verify(decoded);
        
        // Získání nároků (claims) z tokenu
        std::stringstream ss;
        ss << "{";
        
        bool first = true;
        for (auto& e : decoded.get_payload_claims()) {
            if (!first) {
                ss << ",";
            }
            first = false;
            
            ss << "\"" << e.first << "\":";
            
            // Zpracování různých typů nároků
            if (e.second.get_type() == jwt::json::type::string) {
                ss << "\"" << e.second.as_string() << "\"";
            } else if (e.second.get_type() == jwt::json::type::integer) {
                ss << e.second.as_int();
            } else if (e.second.get_type() == jwt::json::type::number) {
                ss << e.second.as_number();
            } else if (e.second.get_type() == jwt::json::type::boolean) {
                ss << (e.second.as_bool() ? "true" : "false");
            } else {
                // Pro ostatní typy použijeme řetězcovou reprezentaci
                ss << "\"" << e.second.to_json().to_str() << "\"";
            }
        }
        
        ss << "}";
        return ss.str();
        
    } catch (const jwt::token_verification_exception& e) {
        // Ověření selhalo
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // Chyba RSA (i když používáme HS256, knihovna může vyvolat obecnou výjimku)
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // Chyba ověření podpisu
        return "{}";
    } catch (const jwt::error::claim_not_present_exception& e) {
        // Chybějící nárok
        return "{}";
    } catch (const std::exception& e) {
        // Obecná chyba
        return "{}";
    } catch (...) {
        // Neočekávaná chyba
        return "{}";
    }
}