#include <iostream>
#include <string>
#include <regex>
#include <tuple>

// 이메일 주소 확인 함수
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식 정의: 유효한 이메일 주소 형식
    const std::regex email_regex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");

    // 이메일 주소가 정규 표현식과 일치하는지 확인
    if (std::regex_match(email, email_regex)) {
        return std::make_tuple(true, "유효한 이메일 주소입니다.");
    } else {
        return std::make_tuple(false, "유효하지 않은 이메일 주소입니다.");
    }
}

// 메인 함수 (테스트용)
int main() {
    // 예제 이메일 주소
    std::string email = "abc.123@def.ghi.com.uk";
    
    // 이메일 체크
    auto [is_valid, message] = check_email(email);
    
    // 결과 출력
    std::cout << message << std::endl;
    
    return 0;
}