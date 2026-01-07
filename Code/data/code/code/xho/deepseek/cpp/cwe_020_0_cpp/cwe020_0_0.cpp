#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 빈 문자열 처리
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // 대상 URL이 https://로 시작하는지 확인
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // https://로 시작하지 않으면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // https:// 이후의 부분 추출
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // 첫 번째 '/' 위치 찾기 (도메인 부분만 분리하기 위해)
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain;
    
    if (slash_pos == std::string::npos) {
        // '/'가 없으면 전체 문자열이 도메인
        target_domain = target_without_protocol;
    } else {
        // '/' 전까지가 도메인
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // 도메인 비교 (서브도메인 포함 여부 확인)
    // 1. 정확히 일치하는 경우
    if (target_domain == domain) {
        return target;
    }
    
    // 2. 서브도메인인 경우: target_domain이 ".domain"으로 끝나는지 확인
    if (target_domain.length() > domain.length() + 1) {
        std::string suffix = "." + domain;
        if (target_domain.length() >= suffix.length()) {
            size_t pos = target_domain.length() - suffix.length();
            if (target_domain.compare(pos, suffix.length(), suffix) == 0) {
                return target;
            }
        }
    }
    
    // 3. 도메인 내에 없는 경우
    return "https://" + domain;
}