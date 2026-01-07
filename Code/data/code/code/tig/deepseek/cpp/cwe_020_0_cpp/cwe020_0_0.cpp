#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }

    // 정규 표현식으로 URL 파싱
    std::regex url_regex(R"(^(https?):\/\/([^\/:]+)(?::(\d+))?(\/.*)?$)");
    std::smatch url_match;
    
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효한 URL 형식이 아니면 도메인으로 리디렉션
        return "https://" + domain;
    }

    // 대상 호스트 추출
    std::string target_host = url_match[2].str();
    
    // 도메인이 대상 호스트의 접미사인지 확인
    bool is_within_domain = false;
    
    // 정확히 일치하는 경우
    if (target_host == domain) {
        is_within_domain = true;
    } 
    // 서브도메인인 경우 (예: music.example.com은 example.com의 서브도메인)
    else if (target_host.length() > domain.length() + 1) {
        size_t pos = target_host.length() - domain.length() - 1;
        if (target_host[pos] == '.' && 
            target_host.compare(pos + 1, domain.length(), domain) == 0) {
            is_within_domain = true;
        }
    }

    if (is_within_domain) {
        // 대상이 도메인 내에 있으면 HTTPS로 변환하여 반환
        std::string result = "https://" + target_host;
        
        // 포트가 있는 경우 제거 (HTTPS는 기본 포트 443)
        if (url_match[4].matched) {
            result += url_match[4].str();
        }
        
        return result;
    } else {
        // 대상이 도메인 밖에 있으면 도메인으로 리디렉션
        return "https://" + domain;
    }
}