#include <string>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 정규 표현식을 사용하여 도메인을 포함하는지 확인
    std::regex domain_regex("https://([a-zA-Z0-9-]+\\.)*" + domain + "(\\:.*)?(/.*)?");
    
    if (std::regex_match(target, domain_regex)) {
        return target; // 도메인이 일치하면 원래 대상 URL 반환
    } else {
        return "https://" + domain; // 일치하지 않으면 도메인 URL로 대체
    }
}