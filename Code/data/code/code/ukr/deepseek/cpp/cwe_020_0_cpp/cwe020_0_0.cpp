#include <string>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 빈 문자열 처리
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // target이 https://로 시작하는지 확인
    std::string https_prefix = "https://";
    if (target.find(https_prefix) != 0) {
        // https://로 시작하지 않으면 도메인으로 리디렉션
        return "https://" + domain;
    }
    
    // https:// 이후의 부분 추출
    std::string target_without_protocol = target.substr(https_prefix.length());
    
    // 첫 번째 '/' 찾기 (도메인 부분만 추출하기 위해)
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain;
    
    if (slash_pos == std::string::npos) {
        // '/'가 없으면 전체 문자열이 도메인
        target_domain = target_without_protocol;
    } else {
        // '/' 이전 부분이 도메인
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // 도메인 비교 (대소문자 구분 없이)
    auto case_insensitive_compare = [](const std::string& str1, const std::string& str2) -> bool {
        if (str1.length() != str2.length()) {
            return false;
        }
        
        for (size_t i = 0; i < str1.length(); ++i) {
            if (std::tolower(static_cast<unsigned char>(str1[i])) != 
                std::tolower(static_cast<unsigned char>(str2[i]))) {
                return false;
            }
        }
        return true;
    };
    
    // target_domain이 domain으로 끝나는지 확인 (서브도메인 포함)
    // 예: music.example.com은 example.com으로 끝남
    if (target_domain.length() >= domain.length()) {
        // target_domain의 끝 부분이 domain과 일치하는지 확인
        std::string target_end = target_domain.substr(target_domain.length() - domain.length());
        
        if (case_insensitive_compare(target_end, domain)) {
            // 도메인이 일치하면 바로 앞에 '.'이 있는지 확인 (music.example.com의 경우)
            if (target_domain.length() == domain.length()) {
                // 정확히 같은 도메인
                return target;
            } else if (target_domain[target_domain.length() - domain.length() - 1] == '.') {
                // 서브도메인인 경우 (예: music.example.com)
                return target;
            }
        }
    }
    
    // 도메인이 일치하지 않으면 기본 도메인으로 리디렉션
    return "https://" + domain;
}