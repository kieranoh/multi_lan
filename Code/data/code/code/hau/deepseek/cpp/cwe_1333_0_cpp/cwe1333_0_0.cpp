#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    // 1. 기본 길이 검사
    if (email.empty()) {
        return std::make_tuple(false, "이메일 주소가 비어 있습니다.");
    }
    
    if (email.length() > 254) { // RFC 5321에 따른 최대 길이
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (최대 254자).");
    }
    
    // 2. @ 기호 검사
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    if (at_pos == 0) {
        return std::make_tuple(false, "로컬 파트가 비어 있습니다.");
    }
    
    // 3. 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    if (domain_part.empty()) {
        return std::make_tuple(false, "도메인 파트가 비어 있습니다.");
    }
    
    // 4. 로컬 파트 검사
    // 로컬 파트 길이 검사 (최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (최대 64자).");
    }
    
    // 로컬 파트 시작/끝 검사
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트는 점으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 연속된 점 검사
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점이 있습니다.");
    }
    
    // 로컬 파트 문자 검사
    for (char c : local_part) {
        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') ||
              c == '!' || c == '#' || c == '$' || c == '%' || c == '&' ||
              c == '\'' || c == '*' || c == '+' || c == '-' || c == '/' ||
              c == '=' || c == '?' || c == '^' || c == '_' || c == '`' ||
              c == '{' || c == '|' || c == '}' || c == '~' || c == '.')) {
            return std::make_tuple(false, "로컬 파트에 허용되지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 5. 도메인 파트 검사
    // 도메인 파트 길이 검사
    if (domain_part.length() > 253) {
        return std::make_tuple(false, "도메인 파트가 너무 깁니다.");
    }
    
    // 도메인 파트 시작/끝 검사
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트는 점으로 시작하거나 끝날 수 없습니다.");
    }
    
    // 연속된 점 검사
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점이 있습니다.");
    }
    
    // 도메인 레이블 분리 및 검사
    size_t start = 0;
    size_t dot_pos;
    int label_count = 0;
    
    do {
        dot_pos = domain_part.find('.', start);
        std::string label;
        
        if (dot_pos == std::string::npos) {
            label = domain_part.substr(start);
        } else {
            label = domain_part.substr(start, dot_pos - start);
        }
        
        label_count++;
        
        // 레이블 길이 검사 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (최대 63자): " + label);
        }
        
        if (label.empty()) {
            return std::make_tuple(false, "빈 도메인 레이블이 있습니다.");
        }
        
        // 레이블 시작/끝 검사
        if (label.front() == '-' || label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블은 하이픈으로 시작하거나 끝날 수 없습니다: " + label);
        }
        
        // 레이블 문자 검사
        for (char c : label) {
            if (!((c >= 'a' && c <= 'z') ||
                  (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') ||
                  c == '-')) {
                return std::make_tuple(false, "도메인 레이블에 허용되지 않은 문자가 있습니다: " + std::string(1, c));
            }
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최소한 2개의 레이블 필요 (예: example.com)
    if (label_count < 2) {
        return std::make_tuple(false, "도메인에 최소한 2개의 레이블이 필요합니다.");
    }
    
    // 최상위 도메인(TLD) 검사
    size_t last_dot = domain_part.find_last_of('.');
    std::string tld = domain_part.substr(last_dot + 1);
    
    if (tld.length() < 2) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
    }
    
    // TLD가 숫자로만 구성되지 않았는지 확인
    bool all_digits = true;
    for (char c : tld) {
        if (!(c >= '0' && c <= '9')) {
            all_digits = false;
            break;
        }
    }
    if (all_digits) {
        return std::make_tuple(false, "최상위 도메인(TLD)은 숫자로만 구성될 수 없습니다.");
    }
    
    // 6. 추가 검증을 위한 정규식 (보조 검증용)
    // RFC 5322 호환 정규식 (간소화된 버전)
    std::regex email_regex(
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)"
    );
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 형식이 올바르지 않습니다.");
    }
    
    // 7. 국제화 도메인 이름(IDN) 지원을 위한 추가 검사
    // 유니코드 문자를 포함할 수 있지만, 여기서는 기본 ASCII 검사만 수행
    // 실제 구현에서는 punycode 변환 등을 추가할 수 있음
    
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}