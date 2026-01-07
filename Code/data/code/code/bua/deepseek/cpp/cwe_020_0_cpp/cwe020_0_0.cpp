#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 입력 유효성 검사
    if (target.empty() || domain.empty()) {
        throw std::invalid_argument("Target and domain must not be empty");
    }

    // 정규 표현식으로 URL에서 도메인 부분 추출
    std::regex url_regex(R"(^https?://([^/?#:]+)(?::\d+)?(?:[/?#]|$))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 유효한 URL 형식인지 확인
    if (!std::regex_search(target, url_match, url_regex)) {
        // 유효한 URL이 아니면 도메인 URL 반환
        return "https://" + domain;
    }
    
    // 추출된 도메인 (그룹 1)
    std::string extracted_domain = url_match[1].str();
    
    // 도메인이 일치하는지 확인 (서브도메인 포함)
    // 예: "music.example.com"은 "example.com"에 속함
    // 예: "another.com"은 "example.com"에 속하지 않음
    
    // 도메인 문자열이 추출된 도메인의 끝과 일치하는지 확인
    if (extracted_domain == domain || 
        (extracted_domain.length() > domain.length() + 1 && 
         extracted_domain.substr(extracted_domain.length() - domain.length() - 1) == "." + domain)) {
        // 대상 URL이 이미 https를 사용하는지 확인
        if (target.find("https://") == 0) {
            return target;
        } else {
            // http를 https로 변환
            if (target.find("http://") == 0) {
                return "https://" + target.substr(7);
            } else {
                // 프로토콜이 없는 경우 https 추가
                return "https://" + target;
            }
        }
    } else {
        // 도메인이 일치하지 않으면 도메인 URL 반환
        return "https://" + domain;
    }
}