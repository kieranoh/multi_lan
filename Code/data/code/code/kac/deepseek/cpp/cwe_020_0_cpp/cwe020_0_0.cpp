#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }

    // 도메인 추출을 위한 정규 표현식
    std::regex url_regex(R"(^(?:https?:\/\/)?([^\/:?#]+)(?:[\/:?#]|$))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL에서 도메인 추출
    if (!std::regex_search(target, url_match, url_regex) || url_match.size() < 2) {
        // 유효한 URL이 아니면 도메인 URL 반환
        return "https://" + domain;
    }
    
    std::string target_domain = url_match[1].str();
    
    // 도메인 비교 (서브도메인 포함 여부 확인)
    // 1. 정확히 일치하는 경우
    if (target_domain == domain) {
        return target.find("://") != std::string::npos ? target : "https://" + target;
    }
    
    // 2. 서브도메인인 경우 확인 (예: music.example.com은 example.com의 서브도메인)
    // 도메인이 대상 도메인의 접미사인지 확인하고, 바로 앞이 '.'인지 확인
    if (target_domain.length() > domain.length() + 1) {
        size_t pos = target_domain.length() - domain.length() - 1;
        if (target_domain[pos] == '.' && target_domain.substr(pos + 1) == domain) {
            // 서브도메인인 경우 원래 대상 URL 반환 (프로토콜이 없는 경우 https 추가)
            return target.find("://") != std::string::npos ? target : "https://" + target;
        }
    }
    
    // 3. 일치하지 않는 경우 도메인 URL 반환
    return "https://" + domain;
}