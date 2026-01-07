#include <jwt.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // JWT tokenaren formatua egiaztatu: hiru atal puntuekin bananduta
        size_t first_dot = token.find('.');
        size_t second_dot = token.find('.', first_dot + 1);
        
        if (first_dot == std::string::npos || second_dot == std::string::npos) {
            throw std::runtime_error("Token formatua baliogabea");
        }
        
        // Tokenaren atalak atera
        std::string header_encoded = token.substr(0, first_dot);
        std::string payload_encoded = token.substr(first_dot + 1, second_dot - first_dot - 1);
        std::string signature_encoded = token.substr(second_dot + 1);
        
        // Base64URL deskodifikatu header eta payload
        std::string header_decoded = jwt::base64_decode(header_encoded);
        std::string payload_decoded = jwt::base64_decode(payload_encoded);
        
        // Header JSON-a parseatu algoritmoa egiaztatzeko
        auto header_json = jwt::decode(header_decoded);
        std::string alg = header_json["alg"].get<std::string>();
        
        // Algoritmoa egiaztatu (HS256 izan behar du)
        if (alg != "HS256") {
            throw std::runtime_error("Algoritmo ez onartua: " + alg);
        }
        
        // Sinadura egiaztatu
        std::string data_to_verify = header_encoded + "." + payload_encoded;
        std::string computed_signature = jwt::sign(jwt::algorithm::hs256{key}, data_to_verify);
        
        // Base64URL formatura bihurtu konputatutako sinadura
        std::string computed_signature_encoded = jwt::base64_encode(
            reinterpret_cast<const unsigned char*>(computed_signature.c_str()), 
            computed_signature.length()
        );
        
        // Sinadurak bat etortzen direla egiaztatu
        if (computed_signature_encoded != signature_encoded) {
            throw std::runtime_error("Sinadura baliogabea");
        }
        
        // Payload JSON-a itzuli string moduan
        return payload_decoded;
        
    } catch (const std::exception& e) {
        // Errore bat gertatuz gero, JSON objektu hutsa itzuli
        return "{}";
    } catch (...) {
        // Salbuespen ezezagun bat gertatuz gero, JSON objektu hutsa itzuli
        return "{}";
    }
}