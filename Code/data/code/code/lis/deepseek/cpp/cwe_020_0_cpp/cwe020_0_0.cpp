#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 정규 표현식으로 URL 파싱
    std::regex url_regex(R"(^(https?)://([^/?#]+)([^?#]*)(?:\?([^#]*))?(?:#(.*))?$)", 
                        std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 유효한지 확인
    if (!std::regex_match(target, url_match, url_regex)) {
        // 유효하지 않은 URL인 경우 도메인 URL 반환
        return "https://" + domain;
    }
    
    // 프로토콜과 호스트 추출
    std::string protocol = url_match[1].str();
    std::string host = url_match[2].str();
    
    // 호스트가 도메인 내에 있는지 확인
    // 서브도메인을 포함한 도메인 매칭 (예: music.example.com은 example.com의 서브도메인)
    if (host == domain || 
        (host.length() > domain.length() + 1 && 
         host.substr(host.length() - domain.length() - 1) == "." + domain)) {
        // 대상 URL이 이미 https인지 확인
        std::string target_protocol = protocol;
        std::transform(target_protocol.begin(), target_protocol.end(), 
                      target_protocol.begin(), ::tolower);
        
        if (target_protocol == "https") {
            return target;  // 이미 https이므로 그대로 반환
        } else {
            // http를 https로 변경
            std::string path = url_match[3].str();
            std::string query = url_match[4].str();
            std::string fragment = url_match[5].str();
            
            std::string result = "https://" + host + path;
            if (!query.empty()) {
                result += "?" + query;
            }
            if (!fragment.empty()) {
                result += "#" + fragment;
            }
            return result;
        }
    } else {
        // 대상 URL이 도메인 내에 없으면 도메인 URL 반환
        return "https://" + domain;
    }
}