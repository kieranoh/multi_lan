#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 기본 도메인 URL 구성
    std::string default_url = "https://" + domain;
    
    // 대상 URL이 비어있는 경우 기본 도메인 반환
    if (target.empty()) {
        return default_url;
    }
    
    // 대상 URL이 https://로 시작하는지 확인
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // https://로 시작하지 않으면 기본 도메인 반환
        return default_url;
    }
    
    // https:// 이후의 부분 추출
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // 첫 번째 '/'의 위치 찾기 (경로 시작점)
    size_t slash_pos = target_without_protocol.find('/');
    
    // 도메인 부분 추출
    std::string target_domain;
    if (slash_pos == std::string::npos) {
        // 경로가 없는 경우 전체가 도메인
        target_domain = target_without_protocol;
    } else {
        // 경로가 있는 경우 첫 번째 '/' 전까지가 도메인
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // 대상 도메인이 제공된 도메인으로 끝나는지 확인
    // example.com이 music.example.com의 끝에 있는지 확인
    if (target_domain.length() >= domain.length()) {
        // 대상 도메인의 끝 부분이 제공된 도메인과 일치하는지 확인
        std::string target_end = target_domain.substr(target_domain.length() - domain.length());
        
        // 정확히 도메인으로 끝나거나, 서브도메인인 경우 (도메인 앞에 '.'이 있는 경우)
        if (target_end == domain) {
            // 정확히 일치하는 경우 (예: example.com == example.com)
            if (target_domain.length() == domain.length()) {
                return target;
            }
            // 서브도메인인 경우 (예: music.example.com)
            // 도메인 앞에 '.'이 있는지 확인
            if (target_domain[target_domain.length() - domain.length() - 1] == '.') {
                return target;
            }
        }
    }
    
    // 대상 도메인이 제공된 도메인 내에 있지 않은 경우 기본 도메인 반환
    return default_url;
}