#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식을 사용하여 이메일 주소의 유효성을 검사합니다.
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    if (std::regex_match(email, email_pattern)) {
        return std::make_tuple(true, "Valid email address");
    } else {
        return std::make_tuple(false, "Invalid email address");
    }
}