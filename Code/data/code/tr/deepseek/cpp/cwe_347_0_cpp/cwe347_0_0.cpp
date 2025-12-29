#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/* JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir JSON nesne dizesi döndür. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // JWT kütüphanesini kullanarak token'ı çöz
        auto decoded = jwt::decode(token);
        
        // JWT'nin algoritmasını kontrol et (HS256 bekleniyor)
        if (decoded.get_algorithm() != "HS256") {
            return "{}";
        }
        
        // Anahtar ile doğrulama yap
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("issuer"); // İsteğe bağlı: issuer kontrolü eklenebilir
        
        verifier.verify(decoded);
        
        // İddiaları JSON formatında döndür
        // JWT kütüphanesi iddiaları std::map olarak sağlar, JSON'a dönüştürmek gerekir
        std::string claims_json = "{";
        
        // Tüm iddiaları JSON formatına dönüştür
        for (const auto& claim : decoded.get_payload_claims()) {
            claims_json += "\"" + claim.first + "\":";
            
            // İddia türüne göre değeri formatla
            if (claim.second.get_type() == jwt::json::type::string) {
                claims_json += "\"" + claim.second.as_string() + "\"";
            } else if (claim.second.get_type() == jwt::json::type::integer) {
                claims_json += std::to_string(claim.second.as_int());
            } else if (claim.second.get_type() == jwt::json::type::number) {
                claims_json += std::to_string(claim.second.as_number());
            } else if (claim.second.get_type() == jwt::json::type::boolean) {
                claims_json += claim.second.as_bool() ? "true" : "false";
            } else {
                // Diğer türler için string olarak ekle
                claims_json += "\"" + claim.second.to_json().to_str() + "\"";
            }
            
            claims_json += ",";
        }
        
        // Son virgülü kaldır ve JSON'u kapat
        if (claims_json.length() > 1) {
            claims_json.pop_back(); // Son virgülü kaldır
        }
        claims_json += "}";
        
        return claims_json;
        
    } catch (const jwt::token_verification_exception& e) {
        // Doğrulama hatası
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // İmza doğrulama hatası
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // RSA hatası (HS256 için gerekli değil ama genel hata yakalama)
        return "{}";
    } catch (const std::exception& e) {
        // Diğer genel hatalar
        return "{}";
    }
}