#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // النمط الأساسي للبريد الإلكتروني (RFC 5322 مبسط)
    std::string pattern1 = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // نمط أكثر صرامة يحد من الأحرف الخاصة في الجزء المحلي
    std::string pattern2 = R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)";
    
    // نمط يتحقق من عدم وجود نقاط متتالية أو في البداية/النهاية
    std::string pattern3 = R"(^(?!\.)(?!.*\.\.)(?!.*@.*@)(?!.*\.$)[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+$)";
    
    // التحقق من أن السلسلة ليست فارغة
    if (email.empty()) {
        return std::make_tuple(false, "empty");
    }
    
    // التحقق من وجود رمز @ واحد على الأقل
    if (std::count(email.begin(), email.end(), '@') != 1) {
        return std::make_tuple(false, "no-single-at");
    }
    
    // تقسيم البريد الإلكتروني إلى جزء محلي ونطاق
    size_t at_pos = email.find('@');
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // التحقق من أن الأجزاء ليست فارغة
    if (local_part.empty() || domain_part.empty()) {
        return std::make_tuple(false, "empty-part");
    }
    
    // التحقق من أن الجزء المحلي لا يبدأ أو ينتهي بنقطة
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "local-dot-boundary");
    }
    
    // التحقق من عدم وجود نقطتين متتاليتين في الجزء المحلي
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive-dots-local");
    }
    
    // التحقق من أن النطاق لا يبدأ أو ينتهي بنقطة
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "domain-dot-boundary");
    }
    
    // التحقق من عدم وجود نقطتين متتاليتين في النطاق
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "consecutive-dots-domain");
    }
    
    // التحقق من أن النطاق يحتوي على نقطة واحدة على الأقل
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "no-dot-in-domain");
    }
    
    // التحقق من طول الجزء المحلي (الحد الأقصى 64 حرفًا حسب RFC)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "local-too-long");
    }
    
    // التحقق من طول النطاق (الحد الأقصى 255 حرفًا حسب RFC)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "domain-too-long");
    }
    
    // التحقق من طول البريد الإلكتروني الكلي (الحد الأقصى 254 حرفًا حسب RFC)
    if (email.length() > 254) {
        return std::make_tuple(false, "email-too-long");
    }
    
    // التحقق من أن جزء النطاق الأخير (TLD) يحتوي على حروف فقط وطوله بين 2 و 63 حرفًا
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    
    // التحقق من أن TLD يحتوي على حروف فقط
    bool tld_has_only_letters = std::all_of(tld.begin(), tld.end(), 
        [](char c) { return std::isalpha(static_cast<unsigned char>(c)); });
    
    if (!tld_has_only_letters) {
        return std::make_tuple(false, "invalid-tld-chars");
    }
    
    // التحقق من طول TLD
    if (tld.length() < 2 || tld.length() > 63) {
        return std::make_tuple(false, "invalid-tld-length");
    }
    
    // تطبيق الأنماط بالترتيب من الأكثر صرامة إلى الأقل
    std::regex regex1(pattern3);
    if (std::regex_match(email, regex1)) {
        return std::make_tuple(true, "strict-pattern");
    }
    
    std::regex regex2(pattern2);
    if (std::regex_match(email, regex2)) {
        return std::make_tuple(true, "common-pattern");
    }
    
    std::regex regex3(pattern1);
    if (std::regex_match(email, regex3)) {
        return std::make_tuple(true, "basic-pattern");
    }
    
    // إذا فشلت جميع الاختبارات
    return std::make_tuple(false, "no-pattern-match");
}