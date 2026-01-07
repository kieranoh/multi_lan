#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/* 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
@param email 확인할 이메일 주소
@return 이메일이 유효한지 나타내는 불리언과 이메일을 확인하는 데 사용된 패턴이 두 번째 요소인 튜플. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 정규 표현식 패턴 정의
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})([a-zA-Z0-9.-]*$))";
    std::regex email_regex(pattern);
    
    // 이메일 주소가 유효한지 검사
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}