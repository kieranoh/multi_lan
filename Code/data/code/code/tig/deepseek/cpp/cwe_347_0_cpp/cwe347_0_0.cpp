#include <jwt.h>
#include <json/json.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cstring>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // 토큰을 '.'으로 분리
        std::vector<std::string> parts;
        std::stringstream tokenStream(token);
        std::string segment;
        
        while (std::getline(tokenStream, segment, '.')) {
            parts.push_back(segment);
        }
        
        // JWT는 header.payload.signature 3부분으로 구성되어야 함
        if (parts.size() != 3) {
            return "{}";
        }
        
        // 헤더와 페이로드 추출
        std::string header = parts[0];
        std::string payload = parts[1];
        std::string signature = parts[2];
        
        // Base64Url 디코딩 함수
        auto base64url_decode = [](const std::string& input) -> std::string {
            std::string base64 = input;
            
            // Base64Url을 Base64로 변환
            for (char& c : base64) {
                if (c == '-') c = '+';
                if (c == '_') c = '/';
            }
            
            // 패딩 추가
            while (base64.length() % 4 != 0) {
                base64 += '=';
            }
            
            // Base64 디코딩 (간단한 구현)
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
        };
        
        // 서명 검증
        std::string data_to_sign = header + "." + payload;
        
        // HMAC-SHA256 계산
        unsigned char hash[SHA256_DIGEST_LENGTH];
        unsigned int hash_len;
        
        HMAC(EVP_sha256(), 
             key.c_str(), key.length(),
             reinterpret_cast<const unsigned char*>(data_to_sign.c_str()), data_to_sign.length(),
             hash, &hash_len);
        
        // 계산된 서명을 Base64Url로 인코딩
        auto base64url_encode = [](const unsigned char* input, size_t length) -> std::string {
            const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            std::string ret;
            int i = 0;
            int j = 0;
            unsigned char char_array_3[3];
            unsigned char char_array_4[4];
            
            while (length--) {
                char_array_3[i++] = *(input++);
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
            
            // Base64Url 변환
            for (char& c : ret) {
                if (c == '+') c = '-';
                if (c == '/') c = '_';
            }
            
            // 패딩 제거
            while (!ret.empty() && ret.back() == '=') {
                ret.pop_back();
            }
            
            return ret;
        };
        
        std::string calculated_signature = base64url_encode(hash, hash_len);
        
        // 서명 비교
        if (calculated_signature != signature) {
            return "{}";
        }
        
        // 페이로드 디코딩 및 JSON 파싱
        std::string decoded_payload = base64url_decode(payload);
        
        // JSON 파싱
        Json::Value claims;
        Json::CharReaderBuilder readerBuilder;
        std::string errors;
        std::istringstream payloadStream(decoded_payload);
        
        if (!Json::parseFromStream(readerBuilder, payloadStream, &claims, &errors)) {
            return "{}";
        }
        
        // JSON을 문자열로 변환
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = ""; // 압축된 JSON
        return Json::writeString(writerBuilder, claims);
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}