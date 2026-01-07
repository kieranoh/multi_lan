#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 검증
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 도메인 정규화: 선행/후행 공백 제거
    std::string normalized_domain = domain;
    normalized_domain.erase(0, normalized_domain.find_first_not_of(" \t\n\r"));
    normalized_domain.erase(normalized_domain.find_last_not_of(" \t\n\r") + 1);

    // URL에서 프로토콜과 도메인 추출을 위한 정규식
    std::regex url_regex(R"(^https?://([^/?#]+))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 유효한 HTTP/HTTPS URL인지 확인
    if (std::regex_search(target, url_match, url_regex)) {
        std::string target_domain = url_match[1].str();
        
        // 서브도메인 포함 여부 확인
        // 1. 정확히 동일한 도메인인 경우
        if (target_domain == normalized_domain) {
            return target;
        }
        
        // 2. 서브도메인인 경우 (예: music.example.com은 example.com의 서브도메인)
        // 도메인으로 끝나는지 확인하고, 바로 앞에 '.'이 있는지 확인
        size_t pos = target_domain.rfind(normalized_domain);
        if (pos != std::string::npos && 
            pos + normalized_domain.length() == target_domain.length() &&
            (pos == 0 || target_domain[pos - 1] == '.')) {
            return target;
        }
    }
    
    // 대상 URL이 도메인 내에 없거나 유효한 URL이 아닌 경우
    // 기본 도메인 URL 생성 (https 프로토콜 사용)
    return "https://" + normalized_domain;
}