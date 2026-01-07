#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 검증
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 정규 표현식으로 URL 파싱
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)(?:\?([^#]*))?(?:#(.*))?$)", 
                        std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 유효한 URL 형식인지 확인
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효하지 않은 URL인 경우 도메인 URL 반환
        return "https://" + domain;
    }
    
    // URL 구성 요소 추출
    std::string protocol = url_match[1].str();
    std::string target_domain = url_match[2].str();
    std::string path = url_match[3].str();
    std::string query = url_match[4].str();
    std::string fragment = url_match[5].str();
    
    // 도메인 비교를 위한 헬퍼 함수
    auto normalize_domain = [](const std::string& domain_str) -> std::string {
        std::string normalized = domain_str;
        
        // 소문자로 변환
        std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        
        // 선행/후행 공백 제거
        normalized.erase(0, normalized.find_first_not_of(" \t\n\r\f\v"));
        normalized.erase(normalized.find_last_not_of(" \t\n\r\f\v") + 1);
        
        return normalized;
    };
    
    std::string normalized_target_domain = normalize_domain(target_domain);
    std::string normalized_domain = normalize_domain(domain);
    
    // 도메인이 일치하는지 확인 (서브도메인 포함)
    auto domain_matches = [&](const std::string& target_domain, const std::string& base_domain) -> bool {
        // 정확히 일치하는 경우
        if (target_domain == base_domain) {
            return true;
        }
        
        // 서브도메인인 경우 확인 (예: music.example.com은 example.com의 서브도메인)
        if (target_domain.length() > base_domain.length() + 1) {
            size_t pos = target_domain.find_last_of('.');
            if (pos != std::string::npos) {
                std::string parent_domain = target_domain.substr(pos + 1);
                if (parent_domain == base_domain) {
                    // 추가 검증: target_domain이 base_domain으로 끝나는지 확인
                    if (target_domain.length() >= base_domain.length() + 2 &&
                        target_domain[target_domain.length() - base_domain.length() - 1] == '.' &&
                        target_domain.substr(target_domain.length() - base_domain.length()) == base_domain) {
                        return true;
                    }
                }
            }
        }
        
        // base_domain으로 끝나는지 확인 (서브도메인 포함)
        if (target_domain.length() > base_domain.length() &&
            target_domain[target_domain.length() - base_domain.length() - 1] == '.' &&
            target_domain.substr(target_domain.length() - base_domain.length()) == base_domain) {
            return true;
        }
        
        return false;
    };
    
    // 도메인이 일치하는 경우 원래 URL 반환 (프로토콜을 https로 강제)
    if (domain_matches(normalized_target_domain, normalized_domain)) {
        // URL 재구성 (항상 https 사용)
        std::string result = "https://" + target_domain + path;
        
        if (!query.empty()) {
            result += "?" + query;
        }
        if (!fragment.empty()) {
            result += "#" + fragment;
        }
        
        return result;
    }
    
    // 도메인이 일치하지 않는 경우 도메인 URL 반환
    return "https://" + domain;
}