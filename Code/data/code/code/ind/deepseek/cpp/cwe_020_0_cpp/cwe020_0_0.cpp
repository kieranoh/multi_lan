#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }

    // 도메인 정규화: 선행/후행 공백 제거
    std::string normalized_domain = domain;
    normalized_domain.erase(0, normalized_domain.find_first_not_of(" \t\n\r\f\v"));
    normalized_domain.erase(normalized_domain.find_last_not_of(" \t\n\r\f\v") + 1);

    if (normalized_domain.empty()) {
        throw std::invalid_argument("도메인이 유효하지 않습니다.");
    }

    // URL 파싱을 위한 정규식 패턴
    std::regex url_pattern(R"(^(https?):\/\/([^\/:\?#]+)(?:[\/:\?#]|$))", std::regex::icase);
    std::smatch url_match;

    // 대상 URL이 유효한 HTTP/HTTPS URL인지 확인
    if (std::regex_search(target, url_match, url_pattern)) {
        std::string target_domain = url_match[2].str();
        
        // 도메인 일치 확인 (대소문자 구분 없이)
        auto target_domain_lower = target_domain;
        auto normalized_domain_lower = normalized_domain;
        std::transform(target_domain_lower.begin(), target_domain_lower.end(), target_domain_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        std::transform(normalized_domain_lower.begin(), normalized_domain_lower.end(), normalized_domain_lower.begin(),
                      [](unsigned char c) { return std::tolower(c); });

        // 대상 도메인이 제공된 도메인으로 끝나는지 확인 (서브도메인 포함)
        if (target_domain_lower == normalized_domain_lower || 
            (target_domain_lower.length() > normalized_domain_lower.length() + 1 &&
             target_domain_lower[target_domain_lower.length() - normalized_domain_lower.length() - 1] == '.' &&
             target_domain_lower.substr(target_domain_lower.length() - normalized_domain_lower.length()) == normalized_domain_lower)) {
            // 대상 URL이 이미 HTTPS인 경우 그대로 반환
            if (url_match[1].str() == "https") {
                return target;
            }
            // HTTP인 경우 HTTPS로 변환
            else {
                return "https" + target.substr(4);
            }
        }
    }

    // 도메인 내에 없거나 유효한 URL이 아닌 경우 도메인 URL 반환
    return "https://" + normalized_domain;
}