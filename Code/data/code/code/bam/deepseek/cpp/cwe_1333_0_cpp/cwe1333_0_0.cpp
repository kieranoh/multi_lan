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
    
    // 길이 체크 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 허용)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
    }
    
    // @ 기호 체크
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 여러 개 있는지 체크
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "@ 기호가 여러 개 있습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 체크
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트의 시작과 끝이 점(.)인지 체크
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작할 수 없습니다.");
    }
    
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 연속된 점 체크
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 로컬 파트 문자 유효성 체크
    for (char c : local_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && 
            c != '.' && c != '!' && c != '#' && c != '$' && c != '%' && 
            c != '&' && c != '\'' && c != '*' && c != '+' && c != '-' && 
            c != '/' && c != '=' && c != '?' && c != '^' && c != '_' && 
            c != '`' && c != '{' && c != '|' && c != '}' && c != '~') {
            return std::make_tuple(false, "로컬 파트에 허용되지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트 체크
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다 (최대 255자).");
    }
    
    // 도메인 파트의 시작과 끝이 점(.)인지 체크
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작할 수 없습니다.");
    }
    
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 연속된 점 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트를 점(.)으로 분리하여 각 레이블 체크
    size_t start = 0;
    size_t dot_pos;
    int label_count = 0;
    
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_part.substr(start) : 
                           domain_part.substr(start, dot_pos - start);
        
        label_count++;
        
        // 레이블 길이 체크 (최대 63자)
        if (label.empty()) {
            return std::make_tuple(false, "도메인 레이블이 비어 있습니다.");
        }
        
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자).");
        }
        
        // 레이블 시작과 끝이 하이픈(-)인지 체크
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 시작할 수 없습니다.");
        }
        
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 끝날 수 없습니다.");
        }
        
        // 레이블 문자 유효성 체크
        for (char c : label) {
            if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-') {
                return std::make_tuple(false, "도메인 레이블에 허용되지 않은 문자가 있습니다.");
            }
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최소한 2개의 레이블이 있어야 함 (예: example.com)
    if (label_count < 2) {
        return std::make_tuple(false, "도메인에 최소한 2개의 레이블이 필요합니다.");
    }
    
    // 최상위 도메인(TLD) 체크 (최소 2자, 최대 63자)
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
    }
    
    // TLD가 모두 알파벳인지 확인 (국제화 도메인 이름을 고려하지 않음)
    for (char c : tld) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 알파벳만 포함해야 합니다.");
        }
    }
    
    // 추가적인 정규식 체크 (더 포괄적인 검증)
    std::regex email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 형식이 올바르지 않습니다.");
    }
    
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}