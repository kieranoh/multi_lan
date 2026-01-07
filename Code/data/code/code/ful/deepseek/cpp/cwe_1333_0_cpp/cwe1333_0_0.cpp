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
    
    // 길이 확인 (일반적으로 254자 제한, 로컬 파트 64자 제한)
    if (email.length() > 254) {
        return std::make_tuple(false, "이메일 주소가 너무 깁니다 (254자 초과).");
    }
    
    // @ 기호 확인
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos) {
        return std::make_tuple(false, "@ 기호가 없습니다.");
    }
    
    // @ 기호가 하나만 있는지 확인
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
    
    // 로컬 파트 길이 확인 (RFC 5321: 최대 64자)
    if (local_part.length() > 64) {
        return std::make_tuple(false, "로컬 파트가 너무 깁니다 (64자 초과).");
    }
    
    // 로컬 파트 시작과 끝이 점(.)인지 확인
    if (local_part.front() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (local_part.back() == '.') {
        return std::make_tuple(false, "로컬 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 연속된 점 확인
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "로컬 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트 시작과 끝이 점(.)인지 확인
    if (domain_part.front() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 시작할 수 없습니다.");
    }
    if (domain_part.back() == '.') {
        return std::make_tuple(false, "도메인 파트가 점(.)으로 끝날 수 없습니다.");
    }
    
    // 도메인 파트에 연속된 점 확인
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, "도메인 파트에 연속된 점(..)이 있습니다.");
    }
    
    // 도메인 파트에 유효한 문자만 있는지 확인
    for (char c : domain_part) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.' && c != '-') {
            return std::make_tuple(false, "도메인 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
        }
    }
    
    // 도메인 파트의 각 레이블 확인
    size_t start = 0;
    size_t dot_pos;
    do {
        dot_pos = domain_part.find('.', start);
        std::string label = domain_part.substr(start, dot_pos - start);
        
        // 레이블 길이 확인 (최대 63자)
        if (label.length() > 63) {
            return std::make_tuple(false, "도메인 레이블이 너무 깁니다 (63자 초과): " + label);
        }
        
        // 레이블이 비어있는지 확인
        if (label.empty()) {
            return std::make_tuple(false, "도메인에 빈 레이블이 있습니다.");
        }
        
        // 레이블 시작과 끝이 하이픈인지 확인
        if (label.front() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 시작할 수 없습니다: " + label);
        }
        if (label.back() == '-') {
            return std::make_tuple(false, "도메인 레이블이 하이픈(-)으로 끝날 수 없습니다: " + label);
        }
        
        start = dot_pos + 1;
    } while (dot_pos != std::string::npos);
    
    // 최상위 도메인(TLD) 확인 (최소 2자 이상)
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot != std::string::npos) {
        std::string tld = domain_part.substr(last_dot + 1);
        if (tld.length() < 2) {
            return std::make_tuple(false, "최상위 도메인(TLD)은 최소 2자 이상이어야 합니다.");
        }
        
        // TLD가 모두 알파벳인지 확인 (일반적인 경우)
        bool all_alpha = std::all_of(tld.begin(), tld.end(), [](char c) {
            return std::isalpha(static_cast<unsigned char>(c));
        });
        
        if (!all_alpha) {
            // 숫자 TLD도 허용 (예: .co.uk의 경우 .uk가 TLD)
            // 하지만 TLD에 하이픈이 있는지 확인
            if (tld.find('-') != std::string::npos) {
                return std::make_tuple(false, "최상위 도메인(TLD)에 하이픈(-)이 있을 수 없습니다.");
            }
        }
    }
    
    // 로컬 파트에 유효한 문자 확인 (더 관대한 검사)
    // 로컬 파트는 알파벳, 숫자, 특수문자 !#$%&'*+-/=?^_`{|}~.를 포함할 수 있음
    for (size_t i = 0; i < local_part.length(); ++i) {
        char c = local_part[i];
        unsigned char uc = static_cast<unsigned char>(c);
        
        if (std::isalnum(uc)) {
            continue;
        }
        
        // 허용되는 특수문자
        std::string special_chars = "!#$%&'*+-/=?^_`{|}~.";
        if (special_chars.find(c) != std::string::npos) {
            // 따옴표로 묶인 로컬 파트는 더 많은 문자를 허용할 수 있지만,
            // 여기서는 일반적인 경우만 처리
            continue;
        }
        
        // @ 기호는 이미 처리되었으므로 여기서는 유효하지 않음
        return std::make_tuple(false, "로컬 파트에 유효하지 않은 문자가 있습니다: " + std::string(1, c));
    }
    
    // 정규식을 사용한 추가 검증 (더 포괄적인 검사)
    // 이 정규식은 RFC 5322를 완전히 준수하지는 않지만 일반적인 이메일 주소를 검증합니다
    std::regex email_regex(R"(^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$)");
    
    if (!std::regex_match(email, email_regex)) {
        return std::make_tuple(false, "이메일 주소 형식이 유효하지 않습니다.");
    }
    
    // 모든 검사를 통과한 경우
    return std::make_tuple(true, "유효한 이메일 주소입니다.");
}