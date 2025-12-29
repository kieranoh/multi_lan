#include <jwt.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <vector>
#include <iomanip>
#include <stdexcept>

namespace {
    // Função auxiliar para decodificar Base64 URL-safe
    std::string base64_url_decode(const std::string& input) {
        std::string base64 = input;
        // Substituir caracteres URL-safe
        for (char& c : base64) {
            if (c == '-') c = '+';
            else if (c == '_') c = '/';
        }
        // Adicionar padding se necessário
        while (base64.size() % 4 != 0) {
            base64.push_back('=');
        }

        BIO* bio = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new_mem_buf(base64.data(), static_cast<int>(base64.size()));
        bio = BIO_push(bio, bmem);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

        std::vector<unsigned char> buffer(base64.size());
        int decoded_length = BIO_read(bio, buffer.data(), static_cast<int>(buffer.size()));
        BIO_free_all(bio);

        if (decoded_length <= 0) {
            return "";
        }
        return std::string(reinterpret_cast<char*>(buffer.data()), decoded_length);
    }

    // Função auxiliar para codificar Base64 URL-safe
    std::string base64_url_encode(const std::string& input) {
        BIO* bio = BIO_new(BIO_f_base64());
        BIO* bmem = BIO_new(BIO_s_mem());
        bio = BIO_push(bio, bmem);
        BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

        BIO_write(bio, input.data(), static_cast<int>(input.size()));
        BIO_flush(bio);

        BUF_MEM* bptr;
        BIO_get_mem_ptr(bio, &bptr);

        std::string result(bptr->data, bptr->length);
        BIO_free_all(bio);

        // Tornar URL-safe
        for (char& c : result) {
            if (c == '+') c = '-';
            else if (c == '/') c = '_';
            else if (c == '=') {
                result.erase(std::find(result.begin(), result.end(), '='), result.end());
                break;
            }
        }
        return result;
    }

    // Função para calcular HMAC SHA256
    std::string hmac_sha256(const std::string& key, const std::string& data) {
        unsigned char* digest = HMAC(EVP_sha256(), 
                                     key.data(), 
                                     static_cast<int>(key.size()),
                                     reinterpret_cast<const unsigned char*>(data.data()), 
                                     data.size(), 
                                     nullptr, 
                                     nullptr);
        
        return std::string(reinterpret_cast<char*>(digest), SHA256_DIGEST_LENGTH);
    }

    // Função para verificar a assinatura
    bool verify_signature(const std::string& header_payload, 
                          const std::string& signature, 
                          const std::string& key) {
        std::string expected_signature = hmac_sha256(key, header_payload);
        std::string decoded_signature = base64_url_decode(signature);
        
        // Comparação segura contra timing attacks
        if (expected_signature.size() != decoded_signature.size()) {
            return false;
        }
        
        int result = 0;
        for (size_t i = 0; i < expected_signature.size(); ++i) {
            result |= expected_signature[i] ^ decoded_signature[i];
        }
        return result == 0;
    }

    // Função para dividir o token JWT
    std::vector<std::string> split_token(const std::string& token) {
        std::vector<std::string> parts;
        std::stringstream ss(token);
        std::string part;
        
        while (std::getline(ss, part, '.')) {
            parts.push_back(part);
        }
        
        if (parts.size() != 3) {
            throw std::runtime_error("Token JWT inválido: deve ter 3 partes separadas por pontos");
        }
        
        return parts;
    }
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Verificar se o token não está vazio
        if (token.empty()) {
            return "{}";
        }

        // Dividir o token em partes
        std::vector<std::string> parts = split_token(token);
        
        // Extrair header, payload e signature
        const std::string& header_encoded = parts[0];
        const std::string& payload_encoded = parts[1];
        const std::string& signature_encoded = parts[2];
        
        // Decodificar header e payload
        std::string header_decoded = base64_url_decode(header_encoded);
        std::string payload_decoded = base64_url_decode(payload_encoded);
        
        if (header_decoded.empty() || payload_decoded.empty()) {
            return "{}";
        }
        
        // Verificar se o algoritmo é HS256
        if (header_decoded.find("\"alg\":\"HS256\"") == std::string::npos &&
            header_decoded.find("\"alg\": \"HS256\"") == std::string::npos) {
            return "{}";
        }
        
        // Verificar a assinatura
        std::string header_payload = header_encoded + "." + payload_encoded;
        if (!verify_signature(header_payload, signature_encoded, key)) {
            return "{}";
        }
        
        // Retornar o payload decodificado
        return payload_decoded;
        
    } catch (const std::exception& e) {
        // Em caso de qualquer erro, retornar objeto JSON vazio
        return "{}";
    } catch (...) {
        // Capturar qualquer outra exceção
        return "{}";
    }
}