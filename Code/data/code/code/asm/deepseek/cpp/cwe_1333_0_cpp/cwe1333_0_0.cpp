#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 체크
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 체크 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 가능)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다.");
    }
    
    // @ 기호 체크
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개인지 체크
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 체크 (RFC 5321)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다.");
    }
    
    // 도메인 파트 길이 체크 (RFC 5321)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다.");
    }
    
    // 로컬 파트의 시작과 끝이 마침표인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 끝날 수 없습니다.");
    }
    
    // 연속된 마침표 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트의 시작과 끝이 마침표나 하이픈인지 체크
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표나 하이픈 체크
    if (domain_part.find("..") != std::string::npos || 
        domain_part.find("--") != std::string::npos ||
        domain_part.find(".-") != std::string::npos ||
        domain_part.find("-.") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 잘못된 문자 시퀀스가 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 체크
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트에 최소한 하나의 마침표가 있는지 체크
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 마침표가 없습니다.");
    }
    
    // 최상위 도메인(TLD) 체크
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인이 너무 짧습니다.");
    }
    
    // TLD에 숫자만 있는지 체크
    bool all_digits = true;
    for (char c : tld) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            all_digits = false;
            break;
        }
    }
    if (all_digits) {
        return std::make_tuple(false, "최상위 도메인이 숫자로만 구성될 수 없습니다.");
    }
    
    // 로컬 파트에 유효한 문자 체크 (더 관대한 검사)
    for (char c : local_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '!' && c != '#' && c != '$' && c != '%' && 
            c != '&' && c != '\'' && c != '*' && c != '+' && c != '-' && 
            c != '/' && c != '=' && c != '?' && c != '^' && c != '_' && 
            c != '`' && c != '{' && c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 정규식을 사용한 추가 검증 (더 포괄적인 패턴)
    std::regex email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 주소 형식이 유효하지 않습니다.");
    }
    
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}