#include <regex>
#include <tuple>
#include <string>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식을 사용하여 이메일 형식 검증
    const std::regex email_pattern(R"(([\w\.-]+)@([\w\.-]+)\.([a-z\.]{2,6}))");
    bool is_valid = std::regex_match(email, email_pattern);
    
    if (is_valid) {
        return std::make_tuple(true, "Valid email address");
    } else {
        return std::make_tuple(false, "Invalid email address");
    }
}