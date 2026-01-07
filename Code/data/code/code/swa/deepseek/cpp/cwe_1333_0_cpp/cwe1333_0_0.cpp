#include <string>
#include <tuple>
#include <regex>
#include <algorithm>

/**
 * 이메일 주소의 유효성을 검사합니다.
 * 
 * 이 함수는 RFC 5322 표준을 기반으로 이메일 주소의 형식을 검증합니다.
 * 로컬 파트와 도메인 파트의 규칙을 따르며, 국제화된 도메인 이름(IDN)도 지원합니다.
 * 
 * @param email 검사할 이메일 주소 문자열
 * @return std::tuple<bool, std::string> 
 *         첫 번째 요소: 유효성 여부 (true: 유효, false: 무효)
 *         두 번째 요소: 검사 결과 메시지 (영어)
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // 빈 문자열 검사
    if (email.empty()) {
        return std::make_tuple(false, "Email address is empty");
    }
    
    // 전체 길이 검사 (RFC 5321 기준: 로컬파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length() > 320) {
        return std::make_tuple(false, "Email address exceeds maximum length of 320 characters");
    }
    
    // @ 기호 검사
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "Email address must contain exactly one '@' character");
    }
    
    // @ 기호가 여러 개인지 검사
    if (email.find('@', at_pos + 1) != std::string::npos) {
        return std::make_tuple(false, "Email address must contain exactly one '@' character");
    }
    
    // 로컬 파트와 도메인 파트 분리
    std::string local_part = email.substr(0, at_pos);
    std::string domain_part = email.substr(at_pos + 1);
    
    // 로컬 파트 검사
    if (local_part.empty()) {
        return std::make_tuple(false, "Local part (before @) cannot be empty");
    }
    
    // 로컬 파트 길이 검사 (RFC 5321 기준: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "Local part exceeds maximum length of 64 characters");
    }
    
    // 로컬 파트의 시작과 끝이 마침표인지 검사
    if (local_part.front() == '.') {
        return std::make_tuple(false, "Local part cannot start with a dot");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "Local part cannot end with a dot");
    }
    
    // 로컬 파트에 연속된 마침표 검사
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "Local part cannot contain consecutive dots");
    }
    
    // 로컬 파트 문자 검사
    for (char c : local_part) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || 
              c == '!' || c == '#' || c == '$' || c == '%' || 
              c == '&' || c == '\'' || c == '*' || c == '+' || 
              c == '-' || c == '/' || c == '=' || c == '?' || 
              c == '^' || c == '_' || c == '`' || c == '{' || 
              c == '|' || c == '}' || c == '~' || c == '.')) {
            return std::make_tuple(false, "Local part contains invalid character");
        }
    }
    
    // 도메인 파트 검사
    if (domain_part.empty()) {
        return std::make_tuple(false, "Domain part (after @) cannot be empty");
    }
    
    // 도메인 파트 길이 검사 (RFC 5321 기준: 최대 255자)
    if (domain_part.length() > 255) {
        return std::make_tuple(false, "Domain part exceeds maximum length of 255 characters");
    }
    
    // 도메인 파트의 시작과 끝이 하이픈이나 마침표인지 검사
    if (domain_part.front() == '-' || domain_part.front() == '.') {
        return std::make_tuple(false, "Domain part cannot start with a hyphen or dot");
    }
    if (domain_part.back() == '-' || domain_part.back() == '.') {
        return std::make_tuple(false, "Domain part cannot end with a hyphen or dot");
    }
    
    // 도메인 파트에 연속된 마침표나 하이픈 검사
    if (domain_part.find("..") != std::string::npos || 
        domain_part.find("--") != std::string::npos) {
        return std::make_tuple(false, "Domain part cannot contain consecutive dots or hyphens");
    }
    
    // 도메인 레이블 분리 및 검사
    size_t start = 0;
    size_t dot_pos;
    int label_count = 0;
    
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = (dot_pos == std::string::npos) ? 
                           domain_part.substr(start) : 
                           domain_part.substr(start, dot_pos - start);
        
        label_count++;
        
        // 레이블 길이 검사 (RFC 1035 기준: 최대 63자)
        if (label.empty()) {
            return std::make_tuple(false, "Domain label cannot be empty");
        }
        if (label.length() > 63) {
            return std::make_tuple(false, "Domain label exceeds maximum length of 63 characters");
        }
        
        // 레이블 문자 검사
        for (char c : label) {
            if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '-')) {
                // 국제화된 도메인 이름(IDN)을 위한 유니코드 문자 허용
                // 실제 구현에서는 punycode 변환 등을 추가할 수 있음
                if (static_cast<unsigned char>(c) > 127) {
                    // IDN 허용 (간단한 검증)
                    continue;
                }
                return std::make_tuple(false, "Domain label contains invalid character");
            }
        }
        
        // 레이블의 시작과 끝이 하이픈인지 검사
        if (label.front() == '-') {
            return std::make_tuple(false, "Domain label cannot start with a hyphen");
        }
        if (label.back() == '-') {
            return std::make_tuple(false, "Domain label cannot end with a hyphen");
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최소한 2개의 레이블이 있어야 함 (예: example.com)
    if (label_count < 2) {
        return std::make_tuple(false, "Domain must have at least two labels");
    }
    
    // 최상위 도메인(TLD) 검사
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "Top-level domain must be at least 2 characters");
        }
        
        // TLD가 모두 알파벳인지 확인 (국가 코드 TLD는 숫자 포함 가능하지만 일반적이지 않음)
        bool all_alpha = std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        });
        
        if (!all_alpha) {
            // 숫자가 포함된 TLD 허용 (예: x.123)
            bool valid_tld_chars = std::all_of(tld.begin(), tld.end(), [](char c) {
                return std::isalnum(static_cast<unsigned char>(c));
            });
            
            if (!valid_tld_chars) {
                return std::make_tuple(false, "Top-level domain contains invalid characters");
            }
        }
    }
    
    // 정규식을 사용한 추가 검증 (선택적, 더 엄격한 검증을 원할 경우)
    // RFC 5322 호환 정규식 패턴
    std::regex email_pattern(
        R"(^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$)",
        std::regex::ECMAScript | std::regex::icase
    );
    
    if (!std::regex_match(email, email_pattern)) {
        // 정규식 검사가 실패하더라도 위의 검증을 통과했다면 허용
        // (정규식은 IDN 등을 완벽히 지원하지 않을 수 있음)
        // 여기서는 경고만 하고 계속 진행
    }
    
    return std::make_tuple(true, "Valid email address");
}