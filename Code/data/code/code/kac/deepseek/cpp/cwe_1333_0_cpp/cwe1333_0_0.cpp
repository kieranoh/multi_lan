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
    
    // 길이 체크 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 허용)
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
        return std::make_tuple(false, "로컬 파트(사용자 이름)가 비어 있습니다.");
    }
    
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 체크
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트(사용자 이름)가 너무 깁니다.");
    }
    
    // 도메인 파트 길이 체크
    if (domain_part.length() > 253) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다.");
    }
    
    // 로컬 파트 시작과 끝이 점인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점으로 시작할 수 없습니다.");
    }
    
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점으로 끝날 수 없습니다.");
    }
    
    // 연속된 점 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점이 있습니다.");
    }
    
    // 도메인 파트 시작과 끝이 점이나 하이픈인지 체크
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 점이나 하이픈으로 시작할 수 없습니다.");
    }
    
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 점이나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 점이나 하이픈 체크
    if (domain_part.find("..") != std::string::npos || 
        domain_part.find("--") != std::string::npos ||
        domain_part.find(".-") != std::string::npos ||
        domain_part.find("-.") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 잘못된 점이나 하이픈 조합이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 체크
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 최상위 도메인(TLD) 체크
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 점이 없습니다.");
    }
    
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.empty()) {
        return std::make_tuple(false, "최상위 도메인(TLD)이 비어 있습니다.");
    }
    
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)이 너무 짧습니다.");
    }
    
    // TLD가 알파벳만 포함하는지 체크
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "최상위 도메인(TLD)에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 로컬 파트에 유효한 문자 체크 (더 관대한 검사)
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        unsigned char uc = static_cast<unsigned char>(c);
        
        // 허용되는 문자: 알파벳, 숫자, 특수 문자 !#$%&'*+-/=?^_`{|}~.
        if (!std::isalnum(uc) && 
            c != '!' && c != '#' && c != '$' && c != '%' && c != '&' && 
            c != '\'' && c != '*' && c != '+' && c != '-' && c != '/' && 
            c != '=' && c != '?' && c != '^' && c != '_' && c != '`' && 
            c != '{' && c != '|' && c != '}' && c != '~' && c != '.') {
            
            // 따옴표로 묶인 문자열 내부는 더 많은 문자를 허용할 수 있음
            // 하지만 간단한 검사를 위해 위의 문자만 허용
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트에 최소한 하나의 점이 있는지 확인 (서브도메인 포함 가능)
    if (std::count(domain_part.begin(), domain_part.end(), '.') == 0) {
        return std::make_tuple(false, "도메인 파트에 점이 없습니다.");
    }
    
    // 모든 검사를 통과하면 유효한 이메일
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}