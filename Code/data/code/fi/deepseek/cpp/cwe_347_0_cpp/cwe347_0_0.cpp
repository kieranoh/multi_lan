#include <jwt.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <iomanip>
#include <algorithm>

namespace {
    // Apufunktio base64-dekoodaukseen (URL-safe)
    std::string base64url_decode(const std::string& input) {
        std::string base64 = input;
        std::replace(base64.begin(), base64.end(), '-', '+');
        std::replace(base64.begin(), base64.end(), '_', '/');
        
        // Lisää padding tarvittaessa
        switch (base64.length() % 4) {
            case 2: base64 += "=="; break;
            case 3: base64 += "="; break;
        }
        
        // Yksinkertainen base64-dekoodaus
        std::string decoded;
        decoded.reserve(base64.length() * 3 / 4);
        
        int val = 0, valb = -8;
        for (unsigned char c : base64) {
            if (c >= 'A' && c <= 'Z') val = (val << 6) + (c - 'A');
            else if (c >= 'a' && c <= 'z') val = (val << 6) + (c - 'a' + 26);
            else if (c >= '0' && c <= '9') val = (val << 6) + (c - '0' + 52);
            else if (c == '+') val = (val << 6) + 62;
            else if (c == '/') val = (val << 6) + 63;
            else if (c == '=') break; // padding
            else throw std::runtime_error("Invalid base64 character");
            
            if (valb >= 0) {
                decoded.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }
        
        return decoded;
    }
    
    // Apufunktio base64-koodaukseen (URL-safe)
    std::string base64url_encode(const unsigned char* input, size_t length) {
        const std::string base64_chars = 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";
        
        std::string ret;
        int i = 0, j = 0;
        unsigned char char_array_3[3], char_array_4[4];
        
        size_t in_len = length;
        const unsigned char* bytes_to_encode = input;
        
        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;
                
                for (i = 0; i < 4; i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }
        
        if (i) {
            for (j = i; j < 3; j++)
                char_array_3[j] = '\0';
            
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for (j = 0; j < i + 1; j++)
                ret += base64_chars[char_array_4[j]];
            
            while (i++ < 3)
                ret += '=';
        }
        
        // Muunna URL-safe muotoon
        std::replace(ret.begin(), ret.end(), '+', '-');
        std::replace(ret.begin(), ret.end(), '/', '_');
        ret.erase(std::remove(ret.begin(), ret.end(), '='), ret.end());
        
        return ret;
    }
    
    // Apufunktio HS256-signatuurin laskemiseen
    std::string calculate_hmac_sha256(const std::string& key, const std::string& data) {
        unsigned char* digest = HMAC(EVP_sha256(), 
                                    key.c_str(), key.length(),
                                    reinterpret_cast<const unsigned char*>(data.c_str()), data.length(),
                                    NULL, NULL);
        
        if (!digest) {
            throw std::runtime_error("HMAC calculation failed");
        }
        
        return std::string(reinterpret_cast<char*>(digest), SHA256_DIGEST_LENGTH);
    }
    
    // Jaa merkkijono osiin erotinmerkin perusteella
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Jaa token osiin
        std::vector<std::string> parts = split(token, '.');
        if (parts.size() != 3) {
            return "{}";
        }
        
        const std::string& header_b64 = parts[0];
        const std::string& payload_b64 = parts[1];
        const std::string& signature_b64 = parts[2];
        
        // Dekoodaa header ja payload
        std::string header_json = base64url_decode(header_b64);
        std::string payload_json = base64url_decode(payload_b64);
        
        // Tarkista signatuuri
        std::string data_to_sign = header_b64 + "." + payload_b64;
        std::string calculated_signature = calculate_hmac_sha256(key, data_to_sign);
        std::string calculated_signature_b64 = base64url_encode(
            reinterpret_cast<const unsigned char*>(calculated_signature.c_str()), 
            calculated_signature.length()
        );
        
        // Vertaa signatuureja
        if (calculated_signature_b64 != signature_b64) {
            return "{}";
        }
        
        // Palauta payload (joka sisältää vaatimukset)
        return payload_json;
        
    } catch (const std::exception& e) {
        // Kaikki poikkeukset johtavat tyhjään JSON-objektiin
        return "{}";
    } catch (...) {
        // Kaikki muut poikkeukset
        return "{}";
    }
}