#include <jwt.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <json/json.h>

namespace {
    // Funzione per decodificare Base64URL
    std::string base64url_decode(const std::string& input) {
        std::string base64 = input;
        std::replace(base64.begin(), base64.end(), '-', '+');
        std::replace(base64.begin(), base64.end(), '_', '/');
        
        // Aggiungi padding se necessario
        switch (base64.length() % 4) {
            case 2: base64 += "=="; break;
            case 3: base64 += "="; break;
        }
        
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new_mem_buf(base64.data(), base64.length());
        bmem = BIO_push(b64, bmem);
        
        BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
        
        char buffer[input.length()];
        int length = BIO_read(bmem, buffer, sizeof(buffer));
        BIO_free_all(bmem);
        
        if (length > 0) {
            return std::string(buffer, length);
        }
        return "";
    }
    
    // Funzione per verificare la firma HMAC-SHA256
    bool verify_signature(const std::string& header_payload, 
                         const std::string& signature, 
                         const std::string& key) {
        unsigned char* digest = HMAC(EVP_sha256(), 
                                    key.data(), key.length(),
                                    reinterpret_cast<const unsigned char*>(header_payload.data()),
                                    header_payload.length(),
                                    NULL, NULL);
        
        if (!digest) return false;
        
        // Converti la firma ricevuta da Base64URL a binario
        std::string received_sig = base64url_decode(signature);
        
        // Confronta le firme
        return (received_sig.length() == SHA256_DIGEST_LENGTH) &&
               (memcmp(digest, received_sig.data(), SHA256_DIGEST_LENGTH) == 0);
    }
    
    // Funzione per estrarre le parti del JWT
    bool parse_jwt_parts(const std::string& token, 
                        std::string& header, 
                        std::string& payload, 
                        std::string& signature) {
        size_t first_dot = token.find('.');
        size_t second_dot = token.find('.', first_dot + 1);
        
        if (first_dot == std::string::npos || second_dot == std::string::npos) {
            return false;
        }
        
        header = token.substr(0, first_dot);
        payload = token.substr(first_dot + 1, second_dot - first_dot - 1);
        signature = token.substr(second_dot + 1);
        
        return !header.empty() && !payload.empty() && !signature.empty();
    }
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Verifica che il token non sia vuoto
    if (token.empty() || key.empty()) {
        return "{}";
    }
    
    std::string header_b64, payload_b64, signature_b64;
    
    // Estrai le parti del JWT
    if (!parse_jwt_parts(token, header_b64, payload_b64, signature_b64)) {
        return "{}";
    }
    
    // Verifica la firma
    std::string header_payload = header_b64 + "." + payload_b64;
    if (!verify_signature(header_payload, signature_b64, key)) {
        return "{}";
    }
    
    // Decodifica il payload
    std::string payload_json = base64url_decode(payload_b64);
    if (payload_json.empty()) {
        return "{}";
    }
    
    // Verifica che il payload sia JSON valido
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errors;
    std::istringstream payload_stream(payload_json);
    
    if (!Json::parseFromStream(readerBuilder, payload_stream, &root, &errors)) {
        return "{}";
    }
    
    // Converti il JSON in stringa
    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["indentation"] = ""; // Nessuna indentazione per output compatto
    std::string result = Json::writeString(writerBuilder, root);
    
    return result;
}