#include <jwt.h>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <vector>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <cstring>
#include <stdexcept>

// Funkcja pomocnicza do dekodowania Base64Url
std::string base64url_decode(const std::string& encoded) {
    std::string base64 = encoded;
    
    // Zamiana Base64Url na standardowy Base64
    for (char& c : base64) {
        if (c == '-') c = '+';
        else if (c == '_') c = '/';
    }
    
    // Dodanie paddingów
    while (base64.length() % 4 != 0) {
        base64 += '=';
    }
    
    // Dekodowanie Base64 (uproszczona implementacja)
    std::string decoded;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    }
    
    int val = 0, valb = -8;
    for (unsigned char c : base64) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            decoded.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    
    return decoded;
}

// Funkcja pomocnicza do obliczania HMAC SHA256
std::string hmac_sha256(const std::string& key, const std::string& data) {
    unsigned char* digest = HMAC(EVP_sha256(), 
                                 key.c_str(), key.length(),
                                 (unsigned char*)data.c_str(), data.length(),
                                 NULL, NULL);
    
    std::string result;
    result.assign((char*)digest, 32); // SHA256 daje 32 bajty
    return result;
}

// Funkcja pomocnicza do dzielenia stringa
std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Podziel token na części
        std::vector<std::string> parts = split_string(token, '.');
        
        if (parts.size() != 3) {
            return "{}"; // Nieprawidłowy format tokenu
        }
        
        std::string header_encoded = parts[0];
        std::string payload_encoded = parts[1];
        std::string signature_encoded = parts[2];
        
        // Dekoduj nagłówek i payload
        std::string header_decoded = base64url_decode(header_encoded);
        std::string payload_decoded = base64url_decode(payload_encoded);
        
        // Weryfikacja sygnatury
        std::string data_to_verify = header_encoded + "." + payload_encoded;
        std::string expected_signature = hmac_sha256(key, data_to_verify);
        
        // Dekoduj otrzymaną sygnaturę
        std::string received_signature = base64url_decode(signature_encoded);
        
        // Porównaj sygnatury (stałe czasowo porównanie)
        if (expected_signature.length() != received_signature.length()) {
            return "{}";
        }
        
        bool signature_valid = true;
        for (size_t i = 0; i < expected_signature.length(); i++) {
            if (expected_signature[i] != received_signature[i]) {
                signature_valid = false;
                break;
            }
        }
        
        if (!signature_valid) {
            return "{}"; // Nieprawidłowa sygnatura
        }
        
        // Zwróć zdekodowany payload
        return payload_decoded;
        
    } catch (const std::exception& e) {
        // W przypadku jakiegokolwiek błędu, zwróć pusty obiekt JSON
        return "{}";
    }
}