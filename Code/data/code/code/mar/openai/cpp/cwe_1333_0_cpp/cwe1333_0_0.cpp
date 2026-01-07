#include <iostream>
#include <regex>
#include <tuple>

/**
 * @brief 주어진 이메일 주소가 유효한지 확인합니다.
 * 
 * @param email 검사할 이메일 주소
 * @return std::tuple<bool, std::string> 유효성 검사 결과와 에러 메시지를 포함하는 튜플
 *        첫 번째 요소는 유효성 결과(true/false), 두 번째 요소는 오류 메시지(유효한 경우 빈 문자열)
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 이메일 정규 표현식
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    
    // 이메일이 패턴에 맞는지 확인
    if (std::regex_match(email, pattern)) {
        return std::make_tuple(true, ""); // 유효한 이메일
    } else {
        return std::make_tuple(false, "Invalid email format."); // 유효하지 않은 이메일
    }
}