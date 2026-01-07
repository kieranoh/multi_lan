#include <string>
#include <cctype>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 도메인이 비어있는 경우 기본 도메인으로 리디렉션
    if (domain.empty()) {
        return "https://";
    }
    
    // 대상 URL이 비어있는 경우 도메인으로 리디렉션
    if (target.empty()) {
        return "https://" + domain;
    }
    
    // 대상 URL이 "https://"로 시작하는지 확인
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // "https://"로 시작하지 않으면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // "https://" 이후의 부분 추출
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // 첫 번째 '/'의 위치 찾기 (도메인 부분과 경로 분리)
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain;
    
    if (slash_pos == std::string::npos) {
        // '/'가 없으면 전체가 도메인
        target_domain = target_without_protocol;
    } else {
        // '/' 이전 부분이 도메인
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    // (서브도메인을 포함한 경우를 처리하기 위해)
    if (target_domain.length() >= domain.length()) {
        // 대상 도메인이 제공된 도메인과 정확히 일치하거나
        // 서브도메인으로 끝나는 경우 확인
        if (target_domain == domain || 
            (target_domain.length() > domain.length() && 
             target_domain[target_domain.length() - domain.length() - 1] == '.' &&
             target_domain.substr(target_domain.length() - domain.length()) == domain)) {
            // 동일한 도메인 내에 있으므로 원래 대상 URL 반환
            return target;
        }
    }
    
    // 다른 도메인에 있으므로 제공된 도메인으로 리디렉션
    return "https://" + domain;
}