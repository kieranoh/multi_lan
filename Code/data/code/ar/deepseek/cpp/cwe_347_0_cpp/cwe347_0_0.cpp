#include <jwt.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // إرجاع سلسلة JSON فارغة إذا كان الرمز أو المفتاح فارغًا
    if (token.empty() || key.empty()) {
        return "{}";
    }
    
    // تهيئة متغيرات libjwt
    jwt_t *jwt = nullptr;
    int ret = 0;
    std::string result = "{}";
    
    try {
        // فك تشفير الرمز باستخدام المفتاح
        ret = jwt_decode(&jwt, token.c_str(), 
                        reinterpret_cast<const unsigned char*>(key.c_str()), 
                        key.size());
        
        // التحقق من نجاح فك التشفير
        if (ret != 0 || jwt == nullptr) {
            throw std::runtime_error("فشل فك تشفير JWT");
        }
        
        // الحصول على المطالبات (claims) من الرمز
        const char *json_claims = jwt_get_grants_json(jwt, nullptr);
        if (json_claims != nullptr) {
            result = json_claims;
        }
        
    } catch (const std::exception& e) {
        // في حالة حدوث خطأ، نعود إلى سلسلة JSON فارغة
        result = "{}";
    }
    
    // تنظيف الذاكرة
    if (jwt != nullptr) {
        jwt_free(jwt);
    }
    
    return result;
}