#include <iostream>
#include <regex>
#include <tuple>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식으로 이메일 형식 검증
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");
    
    // 이메일이 정규 표현식과 일치하는지 확인
    if (std::regex_match(email, email_pattern)) {
        return {true, "Valid email address."};
    } else {
        return {false, "Invalid email address."};
    }
}