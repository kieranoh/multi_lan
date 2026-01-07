#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 체크
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 체크 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 가능)
    if (email.length() > 320) { // 일반적인 최대 길이 제한
        return std::make_tuple(false, "이메일 주소가 너무 깁니다.");
    }
    
    // @ 기호 개수 체크
    size_t at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "정확히 하나의 @ 기호가 필요합니다.");
    }
    
    // @ 기호 위치 찾기
    size_t at_pos = email.find('@');
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트(@ 앞 부분)가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트(@ 뒷 부분)가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 체크 (RFC 5321)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 도메인 파트 길이 체크 (RFC 5321)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다 (최대 255자).");
    }
    
    // 로컬 파트 검사
    // 로컬 파트는 대소문자 알파벳, 숫자, 특수문자 !#$%&'*+-/=?^_`{|}~. 를 포함할 수 있음
    // 단, 점(.)은 연속되거나 시작/끝에 올 수 없음
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트는 점(.)으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 연속된 점 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 로컬 파트 유효 문자 체크
    for (char c : local_part) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || 
              c == '!' || c == '#' || c == '$' || c == '%' || c == '&' || 
              c == '\'' || c == '*' || c == '+' || c == '-' || c == '/' || 
              c == '=' || c == '?' || c == '^' || c == '_' || c == '`' || 
              c == '{' || c == '|' || c == '}' || c == '~' || c == '.')) {
            return std::make_tuple(false, "로컬 파트에 허용되지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트 검사
    // 도메인 파트는 점(.)으로 구분된 레이블들로 구성됨
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트는 점(.)으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 연속된 점 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 레이블 분리 및 검사
    size_t start = 0;
    size_t end = domain_part.find('.');
    while (end != std::string::npos) {
        std::string label = domain_part.substr(start, end - start);
        
        // 레이블 길이 체크 (최대 63자)
        if (label.empty() || label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 비어있거나 너무 깁니다 (최대 63자).");
        }
        
        // 레이블 시작과 끝이 하이픈이 아닌지 체크
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블은 하이픈(-)으로 시작하거나 끝날 수 없습니다.");
        }
        
        // 레이블 문자 체크 (알파벳, 숫자, 하이픈만 허용)
        for (char c : label) {
            if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '-')) {
                return std::make_tuple(false, "도메인 레이블에 허용되지 않은 문자가 있습니다.");
            }
        }
        
        start = end + 1;
        end = domain_part.find('.', start);
    }
    
    // 마지막 레이블 검사
    std::string last_label = domain_part.substr(start);
    if (last_label.empty() || last_label.length() > 63) {
        return std::make_tuple(false, "마지막 도메인 레이블이 비어있거나 너무 깁니다.");
    }
    
    if (last_label.front() == '-' || last_label.back() == '-') {
        return std::make_tuple(false, "마지막 도메인 레이블은 하이픈(-)으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 최상위 도메인(TLD) 체크 (최소 2자 이상, 알파벳만)
    if (last_label.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
    }
    
    for (char c : last_label) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 알파벳만 포함해야 합니다.");
        }
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}