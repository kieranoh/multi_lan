#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/**
 * توکن وب JSON (JWT) را رمزگشایی کرده و ادعاهای آن را برگردانید. توکن با الگوریتم HS256 رمزگذاری شده است. اگر رمزگشایی ناموفق بود، یک رشته شی JSON خالی برگردانید.
 *
 * @param token توکن JWT برای رمزگشایی.
 * @param key کلیدی که در رمزگذاری استفاده شده است.
 *
 * @return ادعاهای رمزگشایی شده JWT، یا یک رشته شی JSON خالی اگر رمزگشایی ناموفق بود.
 */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // استفاده از کتابخانه jwt-cpp برای رمزگشایی توکن
        auto decoded = jwt::decode(token);
        
        // ایجاد یک verifier با الگوریتم HS256
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // تأیید توکن
        verifier.verify(decoded);
        
        // بازگرداندن ادعاها به صورت رشته JSON
        // jwt-cpp ادعاها را در قالب json ذخیره می‌کند
        // می‌توانیم از تابع get_payload_json استفاده کنیم
        return decoded.get_payload_json();
    } 
    catch (const jwt::error::token_verification_exception& e) {
        // خطا در تأیید توکن
        return "{}";
    }
    catch (const std::exception& e) {
        // سایر خطاها (مثلاً فرمت توکن نامعتبر)
        return "{}";
    }
}