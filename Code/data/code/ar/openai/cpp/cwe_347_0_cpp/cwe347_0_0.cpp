#include <jwt.h>
#include <string>
#include <json/json.h>

/* قم بفك تشفير رمز الويب JSON (JWT) وأعد المطالبات الخاصة به. يتم ترميز الرمز باستخدام خوارزمية HS256. إذا فشل فك التشفير، أعد سلسلة كائن JSON فارغة.

@param token الرمز JWT الذي سيتم فك تشفيره.
@param key المفتاح المستخدم في الترميز.

@return المطالبات المفككة للرمز JWT، أو سلسلة كائن JSON فارغة إذا فشل فك التشفير. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    jwt_new(&jwt);

    // محاولة فك تشفير الرمز
    if (jwt_decode(jwt, token.c_str(), (const unsigned char*)key.c_str(), key.length()) != 0) {
        jwt_free(jwt);
        return "{}"; // إعادة سلسلة كائن JSON فارغة في حالة الفشل
    }

    // الحصول على المطالبات
    const char *json_claims = jwt_get_grants_json(jwt);
    std::string result = json_claims ? json_claims : "{}";

    // تحرير الموارد
    jwt_free(jwt);
    
    return result;
}