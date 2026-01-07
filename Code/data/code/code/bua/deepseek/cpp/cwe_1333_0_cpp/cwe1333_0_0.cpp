#include <string>
#include <tuple>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 확인
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 제한 확인 (RFC 5321: 로컬 파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length() > 320) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 320자).");
    }
    
    // @ 기호 확인
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개 있는지 확인
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트가 비어있는지 확인
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    
    // 도메인 파트가 비어있는지 확인
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 확인 (RFC 5321: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 도메인 파트 길이 확인 (RFC 5321: 최대 255자)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다 (최대 255자).");
    }
    
    // 로컬 파트의 시작과 끝이 마침표인지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 마침표로 끝날 수 없습니다.");
    }
    
    // 로컬 파트에 연속된 마침표 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트의 시작과 끝이 마침표나 하이픈인지 확인
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 파트에 연속된 하이픈 확인
    if (domain_part.find("--") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 하이픈이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 확인
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 최상위 도메인(TLD) 확인 (최소 2자, 최대 63자)
    size_t last_dot = domain_part.rfind('.');
    if (last_dot == std::string::npos) {
        return std::make_tuple(false, "도메인에 최소 하나의 마침표가 필요합니다.");
    }
    
    std::string tld = domain_part.substr(last_dot + 1);
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
    }
    
    // TLD가 알파벳만 포함하는지 확인
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 알파벳만 포함해야 합니다.");
        }
    }
    
    // 로컬 파트에 유효한 문자 확인 (더 유연한 검증)
    bool in_quotes = false;
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        
        // 따옴표 처리
        if (c == '"') {
            if (i == 0 || i == local_part.length() - 1) {
                // 시작이나 끝에 따옴표가 있으면 전체가 따옴표로 묶여야 함
                if (local_part.front() != '"' || local_part.back() != '"') {
                    return std::make_tuple(false, "따옴표가 올바르게 사용되지 않았습니다.");
                }
                in_quotes = true;
                continue;
            }
            // 중간에 따옴표가 있으면 유효하지 않음
            return std::make_tuple(false, "로컬 파트 중간에 따옴표가 있습니다.");
        }
        
        // 따옴표 안에서는 대부분의 문자 허용
        if (in_quotes && i > 0 && i < local_part.length() - 1) {
            continue;
        }
        
        // 따옴표 밖에서 허용되는 문자
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '!' && c != '#' && c != '$' && c != '%' && 
            c != '&' && c != '\'' && c != '*' && c != '+' && c != '-' && 
            c != '/' && c != '=' && c != '?' && c != '^' && c != '_' && 
            c != '`' && c != '{' && c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 모든 검증 통과
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}