#include <tuple>
#include <string>
#include <regex>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 이메일 유효성 검사를 위한 정규 표현식 패턴
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);

    return std::make_tuple(is_valid, pattern);
}