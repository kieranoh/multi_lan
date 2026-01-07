#include <iostream>
#include <regex>
#include <tuple>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식 패턴: 이메일 주소 확인
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // 이메일 주소가 유효한지 확인
    bool is_valid = std::regex_match(email, pattern);
    
    // 결과 반환: 유효성 결과와 사용된 패턴
    return std::make_tuple(is_valid, is_valid ? "Valid pattern used" : "Invalid pattern used");
}