#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <regex>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // 도메인 문자열 정규화 (선행/후행 공백 제거)
    std::string normalized_domain = domain;
    normalized_domain.erase(0, normalized_domain.find_first_not_of(" \t\n\r\f\v"));
    normalized_domain.erase(normalized_domain.find_last_not_of(" \t\n\r\f\v") + 1);
    
    if (normalized_domain.empty()) {
        return "https://" + domain;
    }
    
    // URL 파싱을 위한 정규 표현식
    std::regex url_regex(R"(^(https?):\/\/([^\/:\?#]+)(?:[\/:\?#]|$))", 
                        std::regex::icase | std::regex::optimize);
    std::smatch url_match;
    
    // 대상 URL이 유효한 URL인지 확인
    if (!std::regex_search(target, url_match, url_regex)) {
        // 유효한 URL이 아니면 도메인으로 리디렉션
        return "https://" + normalized_domain;
    }
    
    // 대상 URL의 프로토콜과 호스트 추출
    std::string target_protocol = url_match[1].str();
    std::string target_host = url_match[2].str();
    
    // 호스트 이름을 소문자로 변환하여 비교 (도메인은 대소문자 구분 안 함)
    std::string target_host_lower = target_host;
    std::transform(target_host_lower.begin(), target_host_lower.end(),
                   target_host_lower.begin(), ::tolower);
    
    std::string domain_lower = normalized_domain;
    std::transform(domain_lower.begin(), domain_lower.end(),
                   domain_lower.begin(), ::tolower);
    
    // 대상 호스트가 도메인으로 끝나는지 확인 (서브도메인 포함)
    bool is_within_domain = false;
    
    // 정확히 동일한 도메인인 경우
    if (target_host_lower == domain_lower) {
        is_within_domain = true;
    }
    // 서브도메인인 경우 (예: music.example.com이 example.com으로 끝나는지)
    else if (target_host_lower.length() > domain_lower.length() + 1) {
        // 도메인이 호스트 이름의 접미사인지 확인 (점으로 시작)
        if (target_host_lower[target_host_lower.length() - domain_lower.length() - 1] == '.' &&
            target_host_lower.substr(target_host_lower.length() - domain_lower.length()) == domain_lower) {
            is_within_domain = true;
        }
    }
    
    if (is_within_domain) {
        // 대상 URL이 도메인 내에 있으면 HTTPS를 사용하여 반환
        if (target_protocol == "https") {
            return target;
        } else {
            // HTTP를 HTTPS로 변경
            std::string https_target = target;
            https_target.replace(0, 4, "https");
            return https_target;
        }
    } else {
        // 대상 URL이 도메인 내에 없으면 도메인으로 리디렉션
        return "https://" + normalized_domain;
    }
}