#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

// JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं। टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है, तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग लौटाएं।
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    // JWT को डिकोड करने का प्रयास करें
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // डिकोडिंग विफल होने पर खाली JSON ऑब्जेक्ट लौटाएं
        return "{}";
    }
    
    // JWT के दावों को प्राप्त करें
    const char *json_claims = jwt_get_grants_json(jwt);
    std::string claims_json = json_claims ? json_claims : "{}";
    
    // JWT संरचना को मुक्त करें
    jwt_free(jwt);
    
    return claims_json;
}