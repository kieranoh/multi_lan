#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 정규 표현식 패턴
    const std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    std::regex email_regex(pattern);
    
    // 기본 정규 표현식 검사
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, pattern);
    }
    
    // 추가 유효성 검사
    // 1. 전체 길이 검사 (RFC 5321: 로컬 파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length() > 320) {
        return std::make_tuple(false, pattern);
    }
    
    // 2. @ 기호 분리
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 3. 로컬 파트 길이 검사 (RFC 5321: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // 4. 도메인 파트 길이 검사 (RFC 5321: 최대 255자)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, pattern);
    }
    
    // 5. 연속된 점(.) 검사
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 6. 도메인 파트의 연속된 점(.) 검사
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 7. 도메인 파트의 시작/끝 점(.) 검사
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // 8. 최상위 도메인(TLD) 검사 (최소 2자, 알파벳만)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2 || !std::all_of(tld.begin(), tld.end(), 
            [](char c) { return std::isalpha(static_cast<unsigned char>(c)); })) {
            return std::make_tuple(false, pattern);
        }
    }
    
    // 9. 대소문자 무시 도메인 검사를 위한 소문자 변환
    std::string domain_lower = domain_part;
    std::transform(domain_lower.begin(), domain_lower.end(), domain_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // 10. 일반적인 잘못된 도메인 패턴 검사
    const std::vector<std::string> invalid_domains = {
        "example.com", "example.org", "example.net",
        "test.com", "test.org", "test.net",
        "localhost", "localdomain"
    };
    
    for (const auto& invalid : invalid_domains) {
        if (domain_lower.find(invalid) != std::string::npos) {
            // 서브도메인이 아닌 정확한 도메인 매칭 확인
            if (domain_lower == invalid || 
                domain_lower.length() > invalid.length() && 
                domain_lower.substr(domain_lower.length() - invalid.length() - 1) == "." + invalid) {
                return std::make_tuple(false, pattern);
            }
        }
    }
    
    return std::make_tuple(true, pattern);
}