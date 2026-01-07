#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 체크
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    // 길이 체크 (일반적으로 254자 이하, 로컬 파트 64자 이하)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (254자 초과).");
    }
    
    // '@' 문자 개수 체크
    size_t at_count = std::count(email.begin(), email.end(), '@');
    if (at_count != 1) {
        return std::make_tuple(false, "'@' 문자가 1개가 아닙니다.");
    }
    
    // '@' 위치 찾기
    size_t at_pos = email.find('@');
    if (at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, "'@' 문자가 올바른 위치에 없습니다.");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 길이 체크
    if (local_part.empty() || local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 비어있거나 너무 깁니다 (64자 초과).");
    }
    
    // 도메인 파트 길이 체크
    if (domain_part.empty() || domain_part.length() > 253) {
        return std::make_tuple(false, "도메인 파트가 비어있거나 너무 깁니다 (253자 초과).");
    }
    
    // 로컬 파트 검사
    // 로컬 파트는 문자, 숫자, 특수문자(!#$%&'*+-/=?^_`{|}~.)를 포함할 수 있음
    // 단, 점(.)은 연속되거나 시작/끝에 올 수 없음
    if (local_part[0] == '.' || local_part[local_part.length() - 1] == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작하거나 끝납니다.");
    }
    
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 로컬 파트 유효 문자 검사
    for (char c : local_part) {
        if (!(std::isalnum(c) || 
              c == '!' || c == '#' || c == '$' || c == '%' || c == '&' || 
              c == '\'' || c == '*' || c == '+' || c == '-' || c == '/' || 
              c == '=' || c == '?' || c == '^' || c == '_' || c == '`' || 
              c == '{' || c == '|' || c == '}' || c == '~' || c == '.')) {
            return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다.");
        }
    }
    
    // 도메인 파트 검사
    // 도메인 파트는 점(.)으로 구분된 레이블들로 구성됨
    if (domain_part[0] == '.' || domain_part[domain_part.length() - 1] == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작하거나 끝납니다.");
    }
    
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 레이블 분리 및 검사
    std::string label;
    for (size_t i = 0; i <= domain_part.length(); i++) {
        if (i == domain_part.length() || domain_part[i] == '.') {
            // 레이블 검사
            if (label.empty() || label.length() > 63) {
                return std::make_tuple(false, "도메인 레이블이 비어있거나 너무 깁니다 (63자 초과).");
            }
            
            // 레이블은 하이픈(-)으로 시작하거나 끝날 수 없음
            if (label[0] == '-' || label[label.length() - 1] == '-') {
                return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 시작하거나 끝납니다.");
            }
            
            // 레이블은 문자나 숫자로 시작해야 함
            if (!std::isalnum(label[0])) {
                return std::make_tuple(false, "도메인 레이블이 문자나 숫자로 시작하지 않습니다.");
            }
            
            // 레이블 내 문자 검사
            for (char c : label) {
                if (!(std::isalnum(c) || c == '-')) {
                    return std::make_tuple(false, "도메인 레이블에 유효하지 않은 문자가 있습니다.");
                }
            }
            
            label.clear();
        } else {
            label += domain_part[i];
        }
    }
    
    // 최상위 도메인(TLD) 검사 (최소 2자 이상이어야 함, 단 .uk와 같은 국가 코드 TLD는 예외)
    // 실제 구현에서는 공식 TLD 목록과 비교해야 하지만, 여기서는 기본 검사만 수행
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            // .uk, .us 등 2자 국가 코드는 허용, .a, .b 등은 허용하지 않음
            // 실제로는 IANA의 TLD 목록과 비교해야 함
            return std::make_tuple(false, "최상위 도메인(TLD)이 너무 짧습니다.");
        }
    } else {
        return std::make_tuple(false, "도메인에 점(.)이 없습니다.");
    }
    
    // 정규식을 사용한 추가 검사 (RFC 5322 호환)
    std::regex email_regex(
        R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 주소 형식이 올바르지 않습니다.");
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}