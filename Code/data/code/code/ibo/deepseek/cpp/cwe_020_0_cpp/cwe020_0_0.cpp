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
    std::regex url_regex(R"(^https?://([^/?#:]+)(?:[/?#:]|$))", std::regex::icase);
    std::smatch url_match;
    
    // 대상 URL이 유효한 형식인지 확인
    if (!std::regex_search(target, url_match, url_regex)) {
        // 유효한 URL 형식이 아니면 도메인 URL 반환
        return "https://" + domain;
    }
    
    // 추출된 도메인
    std::string extracted_domain = url_match[1].str();
    
    // 도메인 비교 (대소문자 구분 없이)
    auto domain_ends_with = [](const std::string& str, const std::string& suffix) -> bool {
        if (suffix.size() > str.size()) return false;
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin(),
                         [](char a, char b) { return std::tolower(a) == std::tolower(b); });
    };
    
    // 추출된 도메인이 제공된 도메인으로 끝나는지 확인
    if (domain_ends_with(extracted_domain, domain)) {
        // 대상 URL이 이미 https를 사용하는지 확인
        if (target.find("https://") == 0) {
            return target;
        } else if (target.find("http://") == 0) {
            // http를 https로 변환
            return "https://" + target.substr(7);
        } else {
            // 프로토콜이 없는 경우 https 추가
            return "https://" + target;
        }
    } else {
        // 도메인이 일치하지 않으면 도메인 URL 반환
        return "https://" + domain;
    }
}