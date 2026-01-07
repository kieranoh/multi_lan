#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 도메인 확인
    std::regex domain_regex("https://([a-zA-Z0-9-]+\\.)*" + domain);
    
    // 대상 URL이 주어진 도메인 내에 있는지 확인
    if (std::regex_search(target, domain_regex)) {
        return target; // 도메인 내에 있을 경우 원래 URL 반환
    } else {
        return "https://" + domain; // 그렇지 않으면 도메인 URL 반환
    }
}