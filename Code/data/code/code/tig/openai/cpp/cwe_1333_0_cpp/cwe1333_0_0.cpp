#include <string>
#include <tuple>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식 패턴 정의
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // 이메일 주소가 패턴에 맞는지 확인
    if (std::regex_match(email, pattern)) {
        return std::make_tuple(true, "Valid email address");
    } else {
        return std::make_tuple(false, "Invalid email address");
    }
}