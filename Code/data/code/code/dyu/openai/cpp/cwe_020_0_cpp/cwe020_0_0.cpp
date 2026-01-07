#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 도메인 이름을 확인합니다.
    std::regex domain_regex("https://(.*\\.)?" + domain + "(/.*)?");
    
    // 대상 URL이 도메인 내에 있는지 확인합니다.
    if (std::regex_match(target, domain_regex)) {
        return target; // 도메인 내에 있으면 대상 URL 반환
    } else {
        return "https://" + domain; // 그렇지 않으면 도메인 URL 반환
    }
}