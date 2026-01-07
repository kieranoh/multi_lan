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
    std::regex url_regex(R"(^https?://([^/?#:]+)(?::\d+)?(?:/|$))", std::regex::icase);
    std::smatch match;
    
    // 대상 URL이 유효한 URL 형식인지 확인
    if (!std::regex_search(target, match, url_regex)) {
        // 유효한 URL이 아니면 도메인 URL 반환
        return "https://" + domain;
    }
    
    // 추출된 도메인
    std::string extracted_domain = match[1].str();
    
    // 도메인 비교 (대소문자 구분 없이)
    auto case_insensitive_compare = [](char a, char b) {
        return std::tolower(static_cast<unsigned char>(a)) == 
               std::tolower(static_cast<unsigned char>(b));
    };
    
    // 도메인이 일치하는지 확인 (예: example.com이 music.example.com의 끝과 일치)
    bool domain_match = false;
    
    // 정확히 동일한 도메인인 경우
    if (extracted_domain.length() == domain.length()) {
        if (std::equal(extracted_domain.begin(), extracted_domain.end(), 
                      domain.begin(), domain.end(), case_insensitive_compare)) {
            domain_match = true;
        }
    }
    // 서브도메인인 경우 (예: music.example.com은 example.com으로 끝나야 함)
    else if (extracted_domain.length() > domain.length()) {
        // 도메인이 extracted_domain의 끝과 일치하는지 확인
        size_t pos = extracted_domain.length() - domain.length();
        if (extracted_domain[pos - 1] == '.' && 
            std::equal(extracted_domain.begin() + pos, extracted_domain.end(),
                      domain.begin(), domain.end(), case_insensitive_compare)) {
            domain_match = true;
        }
    }
    
    // 도메인이 일치하면 원래 URL 반환, 아니면 도메인 URL 반환
    if (domain_match) {
        // 원래 URL이 http인 경우 https로 변경
        if (target.compare(0, 7, "http://") == 0) {
            return "https://" + target.substr(7);
        }
        // 이미 https인 경우 그대로 반환
        else if (target.compare(0, 8, "https://") == 0) {
            return target;
        }
        // 프로토콜이 없는 경우 https 추가
        else {
            return "https://" + target;
        }
    } else {
        return "https://" + domain;
    }
}