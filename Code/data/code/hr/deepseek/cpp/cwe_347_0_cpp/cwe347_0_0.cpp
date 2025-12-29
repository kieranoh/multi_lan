#include <jwt.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <json/json.h>

// Pomoćna funkcija za base64url dekodiranje
std::string base64url_decode(const std::string& encoded) {
    std::string base64 = encoded;
    for (size_t i = 0; i < base64.size(); ++i) {
        if (base64[i] == '-') base64[i] = '+';
        else if (base64[i] == '_') base64[i] = '/';
    }
    
    while (base64.size() % 4 != 0) {
        base64 += '=';
    }
    
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new_mem_buf(base64.c_str(), base64.length());
    mem = BIO_push(b64, mem);
    
    BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL);
    
    std::vector<char> buffer(base64.length());
    int decoded_length = BIO_read(mem, buffer.data(), buffer.size());
    
    std::string result(buffer.data(), decoded_length);
    
    BIO_free_all(mem);
    return result;
}

// Pomoćna funkcija za base64url kodiranje
std::string base64url_encode(const std::string& data) {
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* mem = BIO_new(BIO_s_mem());
    mem = BIO_push(b64, mem);
    
    BIO_set_flags(mem, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(mem, data.c_str(), data.length());
    BIO_flush(mem);
    
    BUF_MEM* buffer_mem;
    BIO_get_mem_ptr(mem, &buffer_mem);
    
    std::string result(buffer_mem->data, buffer_mem->length);
    
    // Konvertiraj u base64url
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] == '+') result[i] = '-';
        else if (result[i] == '/') result[i] = '_';
        else if (result[i] == '=') {
            result.resize(i);
            break;
        }
    }
    
    BIO_free_all(mem);
    return result;
}

// Pomoćna funkcija za HMAC SHA256
std::string hmac_sha256(const std::string& key, const std::string& data) {
    unsigned char* digest = HMAC(EVP_sha256(), 
                                 key.c_str(), key.length(),
                                 reinterpret_cast<const unsigned char*>(data.c_str()), data.length(),
                                 NULL, NULL);
    
    return std::string(reinterpret_cast<char*>(digest), SHA256_DIGEST_LENGTH);
}

// Glavna funkcija za dekodiranje JWT tokena
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Provjeri je li token prazan
        if (token.empty()) {
            return "{}";
        }
        
        // Podijeli token na dijelove
        std::vector<std::string> parts;
        std::stringstream ss(token);
        std::string part;
        
        while (std::getline(ss, part, '.')) {
            parts.push_back(part);
        }
        
        // JWT mora imati 3 dijela
        if (parts.size() != 3) {
            return "{}";
        }
        
        // Dekodiraj header i payload
        std::string header_json = base64url_decode(parts[0]);
        std::string payload_json = base64url_decode(parts[1]);
        
        // Provjeri signature
        std::string data_to_verify = parts[0] + "." + parts[1];
        std::string expected_signature = hmac_sha256(key, data_to_verify);
        std::string actual_signature = base64url_decode(parts[2]);
        
        // Usporedi signature
        if (expected_signature != actual_signature) {
            return "{}";
        }
        
        // Parsiraj header da provjerimo algoritam
        Json::Value header;
        Json::Reader reader;
        
        if (!reader.parse(header_json, header)) {
            return "{}";
        }
        
        // Provjeri algoritam
        if (!header.isMember("alg") || header["alg"].asString() != "HS256") {
            return "{}";
        }
        
        // Parsiraj payload i vrati kao JSON string
        Json::Value payload;
        if (!reader.parse(payload_json, payload)) {
            return "{}";
        }
        
        Json::StreamWriterBuilder writer;
        writer["indentation"] = "";
        return Json::writeString(writer, payload);
        
    } catch (const std::exception& e) {
        // U slučaju bilo kakve greške, vrati prazan JSON objekt
        return "{}";
    }
}