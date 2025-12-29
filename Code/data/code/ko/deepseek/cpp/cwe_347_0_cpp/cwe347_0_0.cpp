#include <jwt.h>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <vector>
#include <cstdlib>
#include <stdexcept>

std::string base64_decode(const std::string &encoded_string) {
    const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    auto is_base64 = [](unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    };
    
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}

std::string base64_url_decode(const std::string &encoded_string) {
    std::string base64 = encoded_string;
    for (auto &c : base64) {
        if (c == '-') c = '+';
        if (c == '_') c = '/';
    }
    
    switch (base64.length() % 4) {
        case 2: base64 += "=="; break;
        case 3: base64 += "="; break;
    }
    
    return base64_decode(base64);
}

std::string hmac_sha256(const std::string &key, const std::string &data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    HMAC_CTX *ctx = HMAC_CTX_new();
    
    HMAC_Init_ex(ctx, key.c_str(), key.length(), EVP_sha256(), NULL);
    HMAC_Update(ctx, (unsigned char*)data.c_str(), data.length());
    unsigned int len;
    HMAC_Final(ctx, hash, &len);
    HMAC_CTX_free(ctx);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        size_t dot1 = token.find('.');
        size_t dot2 = token.find('.', dot1 + 1);
        
        if (dot1 == std::string::npos || dot2 == std::string::npos) {
            return "{}";
        }
        
        std::string header_encoded = token.substr(0, dot1);
        std::string payload_encoded = token.substr(dot1 + 1, dot2 - dot1 - 1);
        std::string signature_encoded = token.substr(dot2 + 1);
        
        std::string header = base64_url_decode(header_encoded);
        std::string payload = base64_url_decode(payload_encoded);
        
        std::string data_to_verify = token.substr(0, dot2);
        std::string expected_signature = hmac_sha256(key, data_to_verify);
        
        std::string received_signature = base64_url_decode(signature_encoded);
        
        bool signature_valid = true;
        if (expected_signature.length() != received_signature.length() * 2) {
            signature_valid = false;
        } else {
            for (size_t i = 0; i < received_signature.length(); i++) {
                unsigned char c = received_signature[i];
                std::string hex_byte = expected_signature.substr(i * 2, 2);
                unsigned int expected_byte;
                std::stringstream ss;
                ss << std::hex << hex_byte;
                ss >> expected_byte;
                
                if (c != static_cast<unsigned char>(expected_byte)) {
                    signature_valid = false;
                    break;
                }
            }
        }
        
        if (!signature_valid) {
            return "{}";
        }
        
        return payload;
        
    } catch (...) {
        return "{}";
    }
}