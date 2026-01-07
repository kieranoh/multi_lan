#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // RFC 5322 호환 정규식 패턴 (단순화된 버전)
    std::string pattern = R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)";
    
    // 정규식 객체 생성
    std::regex email_regex(pattern);
    
    // 기본 검사
    if (email.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // @ 기호가 정확히 하나 있는지 확인
    int at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, pattern);
    }
    
    // @ 기호 위치 확인
    size_t at_pos = email.find('@');
    if (at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 확인
    if (local_part.empty() || domain_part.empty()) {
        return std::make_tuple(false, pattern);
    }
    
    // 로컬 파트의 시작과 끝이 점이 아닌지 확인
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // 연속된 점 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인 파트의 시작과 끝이 점이 아닌지 확인
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인에 연속된 점 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인 파트에 최소한 하나의 점이 있는지 확인
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // 도메인 파트의 각 레이블 검사
    size_t start = 0;
    size_t dot_pos;
    while ((dot_pos = domain_part.find('.', start)) != std::string::npos) {
        std::string label = domain_part.substr(start, dot_pos - start);
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, pattern);
        }
        // 레이블이 하이픈으로 시작하거나 끝나지 않는지 확인
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, pattern);
        }
        start = dot_pos + 1;
    }
    
    // 마지막 레이블 검사
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || last_label.length() > 63) {
        return std::make_tuple(false, pattern);
    }
    if (last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, pattern);
    }
    
    // 정규식 매칭 검사
    bool is_match = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_match, pattern);
}