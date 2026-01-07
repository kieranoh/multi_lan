#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 이메일 검증을 위한 정규 표현식 패턴
    const std::string pattern = 
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)"
        R"(@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+)"
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)";
    
    std::regex email_regex(pattern);
    
    // 기본 정규식 검증
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, pattern);
    }
    
    // 추가 검증: 도메인 부분에 연속된 점이나 하이픈이 없는지 확인
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    std::string domain = email.substr(at_pos + 1);
    
    // 도메인 부분에 연속된 점이나 하이픈이 있는지 확인
    if (domain.find("..") != std::string::npos || 
        domain.find(".-") != std::string::npos ||
        domain.find("-.") != std::string::npos ||
        domain.find("--") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인이 점으로 시작하거나 끝나지 않는지 확인
    if (domain.front() == '.' || domain.back() == '.' ||
        domain.front() == '-' || domain.back() == '-') {
        return std::make_tuple(false, pattern);
    }
    
    // 최상위 도메인이 최소 2자 이상인지 확인 (예: .com, .uk 등)
    size_t last_dot = domain.find_last_of('.');
    if (last_dot == std::string::npos || last_dot == domain.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    std::string tld = domain.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 부분(골뱅이 앞) 검증
    std::string local_part = email.substr(0, at_pos);
    
    // 로컬 부분이 점으로 시작하거나 끝나지 않는지 확인
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 부분에 연속된 점이 없는지 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 부분 길이 검증 (RFC 기준 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // 전체 이메일 길이 검증 (RFC 기준 최대 254자)
    if (email.length() > 254) {
        return std::make_tuple(false, pattern);
    }
    
    // 모든 검증 통과
    return std::make_tuple(true, pattern);
}