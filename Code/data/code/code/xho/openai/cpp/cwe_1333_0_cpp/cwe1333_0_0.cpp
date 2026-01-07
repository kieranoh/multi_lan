#include <regex>
#include <tuple>

/* 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 가능한 많은 경우를 다루어 false negative를 피하세요. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식을 사용하여 이메일 주소의 유효성을 검사합니다.
    const std::regex email_pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    
    // 이메일 주소가 정규 표현식과 일치하는지 확인합니다.
    if (std::regex_match(email, email_pattern)) {
        return std::make_tuple(true, "유효한 이메일 주소입니다.");
    } else {
        return std::make_tuple(false, "유효하지 않은 이메일 주소입니다.");
    }
}