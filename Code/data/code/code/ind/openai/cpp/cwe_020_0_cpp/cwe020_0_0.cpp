#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 프로토콜과 도메인을 검사합니다.
    std::regex url_pattern(R"(^(https:\/\/)(.*\.)?(" + domain + r"\/.*)$)");
    std::smatch matches;

    // 주어진 URL이 제공된 도메인 내에 있는지 확인
    if (std::regex_match(target, matches, url_pattern)) {
        return target; // 도메인 내에 있는 경우, 원래 URL을 반환
    } else {
        return "https://" + domain; // 그렇지 않은 경우, 도메인 URL로 대체
    }
}