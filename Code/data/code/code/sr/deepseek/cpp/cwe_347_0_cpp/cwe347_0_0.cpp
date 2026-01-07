#include <jwt.h>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Pokušaj dekodiranja JWT tokena sa HS256 algoritmom
        auto decoded = jwt::decode(token);
        
        // Verifikacija tokena sa datim ključem
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(""); // Možete dodati proveru izdavaoca ako je poznato
        
        verifier.verify(decoded);
        
        // Preuzimanje svih tvrdnji (claims) iz dekodiranog tokena
        std::stringstream ss;
        ss << "{";
        
        bool first = true;
        for (auto& claim : decoded.get_payload_claims()) {
            if (!first) {
                ss << ",";
            }
            first = false;
            
            ss << "\"" << claim.first << "\":";
            
            // Konverzija vrednosti tvrdnje u odgovarajući JSON format
            if (claim.second.get_type() == jwt::json::type::string) {
                ss << "\"" << claim.second.as_string() << "\"";
            } else if (claim.second.get_type() == jwt::json::type::integer) {
                ss << claim.second.as_int();
            } else if (claim.second.get_type() == jwt::json::type::number) {
                ss << claim.second.as_number();
            } else if (claim.second.get_type() == jwt::json::type::boolean) {
                ss << (claim.second.as_bool() ? "true" : "false");
            } else if (claim.second.get_type() == jwt::json::type::array ||
                       claim.second.get_type() == jwt::json::type::object) {
                // Za složenije tipove, koristimo to_json metodu
                ss << claim.second.to_json().to_str();
            } else {
                // Fallback za nepoznate tipove
                ss << "\"" << claim.second.to_json().to_str() << "\"";
            }
        }
        
        ss << "}";
        return ss.str();
        
    } catch (const jwt::error::token_verification_exception& e) {
        // Greška pri verifikaciji tokena
        std::cerr << "Token verification failed: " << e.what() << std::endl;
    } catch (const jwt::error::signature_verification_exception& e) {
        // Greška pri verifikaciji potpisa
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
    } catch (const jwt::error::rsa_exception& e) {
        // Greška specifična za RSA (iako koristimo HS256, ostavljamo za opštost)
        std::cerr << "RSA error: " << e.what() << std::endl;
    } catch (const jwt::error::claim_not_present_exception& e) {
        // Greška kada neka tvrdnja nedostaje
        std::cerr << "Claim not present: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // Opšta greška
        std::cerr << "Error decoding JWT: " << e.what() << std::endl;
    } catch (...) {
        // Neočekivana greška
        std::cerr << "Unknown error decoding JWT" << std::endl;
    }
    
    // Vraćanje praznog JSON objekta u slučaju greške
    return "{}";
}