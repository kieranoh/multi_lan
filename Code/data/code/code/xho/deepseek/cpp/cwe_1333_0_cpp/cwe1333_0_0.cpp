#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 체크
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 체크 (RFC 5321 기준: 로컬파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length() > 320) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 320자).");
    }
    
    // @ 기호 개수 체크
    size_t at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "@ 기호가 " + std::to_string(at_count) + "개 포함되어 있습니다 (정확히 1개여야 합니다).");
    }
    
    // @ 기호 위치 찾기
    size_t at_pos = email.find('@');
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 검사
    if (local_part.empty()) {
        return std::make_tuple(false, "로컬 파트(@ 앞 부분)가 비어 있습니다.");
    }
    
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트 시작과 끝이 마침표인지 체크
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
    
    // 로컬 파트 유효 문자 체크
    for (char c : local_part) {
        if (!(std::isalnum(c) || c == '.' || c == '!' || c == '#' || c == '$' || 
              c == '%' || c == '&' || c == '\'' || c == '*' || c == '+' || 
              c == '-' || c == '/' || c == '=' || c == '?' || c == '^' || 
              c == '_' || c == '`' || c == '{' || c == '|' || c == '}' || c == '~')) {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다: '" + std::string(1, c) + "'");
        }
    }
    
    // 도메인 파트 검사
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트(@ 뒷 부분)가 비어 있습니다.");
    }
    
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다 (최대 255자).");
    }
    
    // 도메인 파트 시작과 끝이 마침표나 하이픈인지 체크
    if (domain_part.front() == '.' || domain_part.front() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 시작할 수 없습니다.");
    }
    
    if (domain_part.back() == '.' || domain_part.back() == '-') {
        return std::make_tuple(false, "도메인 파트가 마침표나 하이픈으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 마침표 체크
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 마침표가 있습니다.");
    }
    
    // 도메인 레이블 분리 및 검사
    std::string domain_copy = domain_part;
    size_t start = 0;
    size_t dot_pos;
    
    do {
        dot_pos = domain_copy.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_copy.substr(start) : 
                           domain_copy.substr(start, dot_pos - start);
        
        // 레이블 길이 체크 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블 '" + label + "'이 너무 깁니다 (최대 63자).");
        }
        
        // 레이블이 비어있는지 체크
        if (label.empty()) {
            return std::make_tuple(false, "도메인 파트에 빈 레이블이 있습니다.");
        }
        
        // 레이블 문자 체크
        for (char c : label) {
            if (!(std::isalnum(c) || c == '-')) {
                return std::make_tuple(false, "도메인 레이블에 유효하지 않은 문자가 있습니다: '" + std::string(1, c) + "'");
            }
        }
        
        // 레이블 시작과 끝이 하이픈인지 체크
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블 '" + label + "'이 하이픈으로 시작할 수 없습니다.");
        }
        
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블 '" + label + "'이 하이픈으로 끝날 수 없습니다.");
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최상위 도메인(TLD) 체크 (최소 2자, 알파벳만)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
        }
        
        for (char c : tld) {
            if (!std::isalpha(c)) {
                return std::make_tuple(false, "최상위 도메인(TLD)은 알파벳만 포함해야 합니다.");
            }
        }
    } else {
        // 점이 없는 경우 전체 도메인이 TLD
        if (domain_part.length() < 2) {
            return std::make_tuple(false, "도메인은 최소 2자 이상이어야 합니다.");
        }
        
        for (char c : domain_part) {
            if (!std::isalpha(c)) {
                return std::make_tuple(false, "도메인은 알파벳만 포함해야 합니다 (점이 없는 경우).");
            }
        }
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}