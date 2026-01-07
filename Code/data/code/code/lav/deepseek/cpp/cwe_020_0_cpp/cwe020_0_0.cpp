#include <string>
#include <cctype>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 빈 문자열 처리
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // 대상 URL이 https://로 시작하는지 확인
    std::string target_lower = target;
    std::transform(target_lower.begin(), target_lower.end(), target_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // https://로 시작하지 않으면 도메인으로 리디렉션
    if (target_lower.find("https://") != 0) {
        return "https://" + domain;
    }
    
    // https://를 제외한 부분 추출
    std::string target_without_protocol = target.substr(8); // "https://"의 길이는 8
    
    // 도메인 추출 (첫 번째 '/' 전까지)
    std::string target_domain;
    size_t slash_pos = target_without_protocol.find('/');
    if (slash_pos != std::string::npos) {
        target_domain = target_without_protocol.substr(0, slash_pos);
    } else {
        target_domain = target_without_protocol;
    }
    
    // 도메인 비교 (대소문자 구분 없이)
    std::string target_domain_lower = target_domain;
    std::transform(target_domain_lower.begin(), target_domain_lower.end(), target_domain_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    std::string domain_lower = domain;
    std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인 (서브도메인 포함)
    // 예: music.example.com은 example.com으로 끝남
    if (target_domain_lower == domain_lower || 
        (target_domain_lower.length() > domain_lower.length() + 1 &&
         target_domain_lower[target_domain_lower.length() - domain_lower.length() - 1] == '.' &&
         target_domain_lower.substr(target_domain_lower.length() - domain_lower.length()) == domain_lower)) {
        // 대상 URL 반환
        return target;
    }
    
    // 도메인이 일치하지 않으면 도메인 URL로 대체
    return "https://" + domain;
}