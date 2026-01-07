#include <jwt.h>
#include <string>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Deklarera variabler för att lagra avkodade data
        jwt::jwt_object decoded;
        
        // Försök avkoda token med den angivna nyckeln
        decoded = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
        
        // Returnera påståendena som en JSON-sträng
        return decoded.payload().to_json();
    } 
    catch (const jwt::TokenExpiredError& e) {
        // Token har utgått
        return "{}";
    }
    catch (const jwt::SignatureFormatError& e) {
        // Ogiltigt signaturformat
        return "{}";
    }
    catch (const jwt::DecodeError& e) {
        // Allmänt avkodningsfel
        return "{}";
    }
    catch (const jwt::VerificationError& e) {
        // Verifieringsfel (t.ex. ogiltig signatur)
        return "{}";
    }
    catch (const std::exception& e) {
        // Alla andra undantag
        return "{}";
    }
}