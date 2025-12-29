#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;
    try {
        // JWT'yi çöz
        jwt_obj = jwt::decode(token);

        // HS256 ile imzalanmışsa, doğrula
        jwt_obj.verify(jwt::params::algorithms({"HS256"}).secret(key));

        // İddiaları JSON formatında döndür
        return jwt_obj.payload().to_json().dump();
    } catch (const std::exception& e) {
        // Hata durumunda boş bir JSON nesne dizesi döndür
        return "{}";
    }
}