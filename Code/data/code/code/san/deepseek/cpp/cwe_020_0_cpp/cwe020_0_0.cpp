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
        // https://로 시작하지 않으면 도메인 URL 반환
        return "https://" + domain;
    }
    
    // https:// 이후의 부분 추출
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // 도메인 부분 추출 (첫 번째 '/' 이전까지)
    std::string target_domain;
    size_t slash_pos = target_without_protocol.find('/');
    if (slash_pos != std::string::npos) {
        target_domain = target_without_protocol.substr(0, slash_pos);
    } else {
        target_domain = target_without_protocol;
    }
    
    // 도메인 비교
    // 서브도메인을 포함한 도메인이 제공된 도메인으로 끝나는지 확인
    // 예: music.example.com은 example.com으로 끝남
    if (target_domain.length() >= domain.length()) {
        // 대상 도메인이 제공된 도메인으로 끝나는지 확인
        if (target_domain.compare(target_domain.length() - domain.length(), 
                                  domain.length(), domain) == 0) {
            // 정확히 도메인으로 끝나는지 확인 (서브도메인인 경우 점이 있어야 함)
            if (target_domain.length() == domain.length() || 
                target_domain[target_domain.length() - domain.length() - 1] == '.') {
                // 대상 URL이 제공된 도메인 내에 있음
                return target;
            }
        }
    }
    
    // 대상 URL이 제공된 도메인 내에 없으면 도메인 URL 반환
    return "https://" + domain;
}