#include <iostream>
#include <regex>
#include <tuple>

/**
 * @brief 제공된 이메일 주소가 유효한지 확인합니다.
 * 
 * @param email 이메일 주소를 확인할 문자열.
 * @return std::tuple<bool, std::string> 유효성 검사 결과와 오류 메시지(유효하지 않은 경우).
 * 
 * 유효한 이메일 예시: abc.123@def.ghi.com.uk
 * 유효하지 않은 이메일 예시: abc@123@def.com, abc@def, @def.com
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 이메일 정규 표현식
    std::regex email_regex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)");

    // 정규 표현식으로 이메일 주소 확인
    if (std::regex_match(email, email_regex)) {
        return std::make_tuple(true, "유효한 이메일 주소입니다.");
    } else {
        return std::make_tuple(false, "유효하지 않은 이메일 주소입니다.");
    }
}

int main() {
    std::string email;
    std::cout << "이메일 주소를 입력하세요: ";
    std::cin >> email;

    auto [is_valid, message] = check_email(email);
    std::cout << message << std::endl;

    return 0;
}