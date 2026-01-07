#include <tuple>
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 확인
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 확인 (일반적으로 최대 254자, 로컬 파트 최대 64자)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
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
    
    // 로컬 파트와 도메인 파트가 비어있는지 확인
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 로컬 파트 길이 확인 (최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트가 .으로 시작하거나 끝나는지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 .으로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 .으로 끝날 수 없습니다.");
    }
    
    // 로컬 파트에 연속된 .이 있는지 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 .이 있습니다.");
    }
    
    // 도메인 파트가 .으로 시작하거나 끝나는지 확인
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 .으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 .으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 .이 있는지 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 .이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 확인
    for (char c : domain_part) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '.' || c == '-')) {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트에 최소 하나의 .이 있는지 확인
    if (domain_part.find('.') == std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 최소 하나의 .이 필요합니다.");
    }
    
    // 도메인 레이블 확인 (도메인을 .으로 분리)
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_part.substr(start) : 
                           domain_part.substr(start, dot_pos - start);
        
        // 레이블이 비어있는지 확인
        if (label.empty()) {
            return std::make_tuple(false, "도메인 레이블이 비어 있습니다.");
        }
        
        // 레이블 길이 확인 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
        }
        
        // 레이블이 -로 시작하거나 끝나는지 확인
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 -로 시작할 수 없습니다.");
        }
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 -로 끝날 수 없습니다.");
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최상위 도메인(TLD) 확인 (최소 2자, 숫자만으로 구성되지 않음)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
        }
        
        // TLD가 숫자만으로 구성되었는지 확인
        bool all_digits = true;
        for (char c : tld) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                all_digits = false;
                break;
            }
        }
        if (all_digits) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 숫자만으로 구성될 수 없습니다.");
        }
    }
    
    // 로컬 파트에 유효한 문자 확인 (더 유연한 검사)
    // RFC 5322를 완전히 준수하지는 않지만 일반적인 경우를 다룸
    bool in_quotes = false;
    bool escape_next = false;
    
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        
        if (escape_next) {
            escape_next = false;
            continue;
        }
        
        if (c == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        
        if (in_quotes) {
            if (c == '\\') {
                escape_next = true;
            }
            // 따옴표 안에서는 대부분의 문자 허용
            continue;
        }
        
        // 따옴표 밖에서 허용되는 문자
        if (!(std::isalnum(static_cast<unsigned char>(c)) || 
              c == '.' || c == '!' || c == '#' || c == '$' || 
              c == '%' || c == '&' || c == '\'' || c == '*' || 
              c == '+' || c == '-' || c == '/' || c == '=' || 
              c == '?' || c == '^' || c == '_' || c == '`' || 
              c == '{' || c == '|' || c == '}' || c == '~')) {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 따옴표가 짝이 맞는지 확인
    if (in_quotes) {
        return std::make_tuple(false, "로컬 파트의 따옴표가 짝이 맞지 않습니다.");
    }
    
    // 모든 검사를 통과하면 유효한 이메일
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}