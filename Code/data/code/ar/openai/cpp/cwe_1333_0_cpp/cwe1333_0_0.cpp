#include <iostream>
#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // تعريف نمط التعبير النمطي للتحقق من صلاحية عنوان البريد الإلكتروني
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // التحقق مما إذا كان البريد الإلكتروني يتطابق مع النمط
    bool is_valid = std::regex_match(email, pattern);
    
    // إرجاع النتيجة مع النمط المستخدم
    return std::make_tuple(is_valid, pattern.str());
}