#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj = jwt::decode(token);
    
    // Verifica a assinatura
    try {
        jwt_obj.verify(jwt::params::alg("HS256"), key);
    } catch (const std::exception& e) {
        return "{}"; // Retorna uma string de objeto JSON vazia em caso de falha na verificação
    }
    
    // Converte as reivindicações em uma string JSON
    return jwt_obj.payload().dump();
}