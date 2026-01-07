#include <tuple>
#include <string>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 이메일 검증을 위한 정규 표현식 패턴
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex email_regex(pattern);
    
    // 이메일이 유효한지 검사
    bool is_valid = std::regex_match(email, email_regex);
    
    // 결과를 튜플로 반환
    return std::make_tuple(is_valid, pattern);
}