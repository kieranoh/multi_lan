#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 도메인 추출을 위한 정규 표현식
    std::regex url_regex(R"(^https?://([^/?#:]+)(?::\d+)?(?:[/?#]|$))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL에서 도메인 추출
    if (std::regex_search(target, url_match, url_regex) && url_match.size() > 1) {
        std::string target_domain = url_match[1].str();
        
        // 도메인 비교 (대소문자 구분 없이)
        auto domain_compare = [](const std::string& a, const std::string& b) {
            return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
        };
        
        // 대상 도메인이 제공된 도메인으로 끝나는지 확인 (서브도메인 포함)
        if (target_domain.size() >= domain.size()) {
            // 도메인 끝부분 비교
            std::string target_end = target_domain.substr(target_domain.size() - domain.size());
            if (domain_compare(target_end, domain)) {
                // 정확히 일치하거나 서브도메인인 경우
                if (target_domain.size() == domain.size() || 
                    target_domain[target_domain.size() - domain.size() - 1] == '.') {
                    // 원래 대상 URL을 https로 반환
                    if (target.find("https://") == 0) {
                        return target;
                    } else if (target.find("http://") == 0) {
                        return "https://" + target.substr(7);
                    } else {
                        // 프로토콜이 없는 경우 https 추가
                        return "https://" + target;
                    }
                }
            }
        }
    }
    
    // 도메인이 일치하지 않으면 제공된 도메인으로 https URL 반환
    return "https://" + domain;
}